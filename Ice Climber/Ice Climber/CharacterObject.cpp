#include "CharacterObject.h"
#include <DxLib.h>
#include <cassert>
#include "Camera.h"
#include "Game.h"


//アニメーションの変更
void CharacterObject::ChangeAction(const char * name)
{
	_nowName = name;
	_nowCutIdx = 0;
	_frame = 0;
}

//アニメーションのフレームを1進める
bool CharacterObject::ProceedAnimationFrame()
{
	if ((signed)_frame < _actionData.actInfo[_nowName].cuts[_nowCutIdx].duration) {
		_frame++;
	}
	else {
		_frame = 0;
		if (_nowCutIdx < (signed)_actionData.actInfo[_nowName].cuts.size() - 1) {
			++_nowCutIdx;
		}
		else {
			if (_actionData.actInfo[_nowName].isLoop) {
				_nowCutIdx = 0;
			}
			else {
				return true;
			}
		}
	}
	return false;
}

///ファイルの読み込み
void CharacterObject::readActfile(const char * actionPath)
{
	int h = DxLib::FileRead_open(actionPath, false);

	float version = 0.0f;
	DxLib::FileRead_read(&version, sizeof(version), h);
	assert(version == 1.01f);

	int imgpathsize = 0;
	DxLib::FileRead_read(&imgpathsize, sizeof(imgpathsize), h);

	std::string imgPath = "";
	imgPath.resize(imgpathsize);

	DxLib::FileRead_read(&imgPath[0], imgpathsize, h);

	std::string actPath = actionPath;

	auto ipos = actPath.find_last_of("/") + 1;
	_actionData.imgFilePath = actPath.substr(0, ipos) + imgPath;
	///このアプリケーションからの相対パスにする

	//アクションの数
	int actionCount = 0;
	DxLib::FileRead_read(&actionCount, sizeof(actionCount), h);

	for (int idx = 0; idx < actionCount; ++idx) {
		//アクションの名前
		int actionNameSize = 0;
		DxLib::FileRead_read(&actionNameSize, sizeof(actionNameSize), h);
		std::string actionName;
		actionName.resize(actionNameSize);
		DxLib::FileRead_read(&actionName[0], actionName.size(), h);

		ActionInfo actInfo;

		//ループ読み込み
		DxLib::FileRead_read(&actInfo.isLoop, sizeof(actInfo.isLoop), h);

		//カットデータ数の取得
		int cutCount = 0;
		DxLib::FileRead_read(&cutCount, sizeof(cutCount), h);

		//カットデータ取得
		actInfo.cuts.resize(cutCount);
		for (int i = 0; i < cutCount; i++) {
			DxLib::FileRead_read(&actInfo.cuts[i], sizeof(actInfo.cuts[i]) - sizeof(actInfo.cuts[i].actrects), h);

			//アクション矩形の読み込み
			int actrcCount = 0;
			DxLib::FileRead_read(&actrcCount, sizeof(actrcCount), h);

			if (actrcCount == 0)continue;
			actInfo.cuts[i].actrects.resize(actrcCount);
			DxLib::FileRead_read(&actInfo.cuts[i].actrects[0], actrcCount * sizeof(ActionRect), h);
		}

		//アクションマップに登録
		_actionData.actInfo[actionName] = actInfo;
	}
	DxLib::FileRead_close(h);
}

void CharacterObject::Draw(int & Img)
{
	Game& game = Game::Instance();

	auto& actInfo = _actionData.actInfo[_nowName];
	auto& cut = actInfo.cuts[_nowCutIdx];
	auto& rc = cut.rc;
	auto centerX = _isTurn ? rc.Width() - cut.center.x : cut.center.x;

	Position2f pos = _camera.CalculatePosition(_pos);
	auto _tmp = _camera.GetViewport();
	auto scroll = _tmp.Top();//上スクロール値算出
	scroll %= (bgimg_y_size + bnimg_y_size + unimg_y_size) * 2;
	DxLib::DrawRectRotaGraph2((int)pos.x, (int)pos.y-scroll, rc.Left(), rc.Top(), rc.Width(), rc.Height(), centerX, cut.center.y, (int)game.GetObjectScale(), 0.0, Img, true, _isTurn);
#ifdef _DEBUG
	DebugDraw();
#endif
}

void CharacterObject::DebugDraw()
{
	///矩形の表示
	Game& game = Game::Instance();

	auto& actInfo = _actionData.actInfo[_nowName];
	auto& cut = actInfo.cuts[_nowCutIdx];

	auto _tmp = _camera.GetViewport();
	auto scroll = _tmp.Top();//上スクロール値算出
	scroll %= (bgimg_y_size + bnimg_y_size + unimg_y_size) * 2;

	for (ActionRect& act : cut.actrects) {
		Rect rc = GetActuralRectForAction(act.rc);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		DrawBox(rc.Left(), rc.Top()-scroll, rc.Right(), rc.Bottom()-scroll, 0xff0000, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		DrawBox(rc.Left(), rc.Top()-scroll, rc.Right(), rc.Bottom()-scroll, 0xff0000, false);
	}
}

Rect CharacterObject::GetActuralRectForAction(const Rect & _rec) const
{
	Game& game = Game::Instance();

	Rect rc = _rec;
	rc.size.width *= (int)game.GetObjectScale();
	rc.size.height *= (int)game.GetObjectScale();
	auto offset = _isTurn ? rc.size.width : rc.size.width / 2;
	Position2f pos = _camera.CalculatePosition(_pos);
	rc.center.x = rc.center.x * (int)game.GetObjectScale() + (int)pos.x - offset;
	rc.center.y = rc.center.y * (int)game.GetObjectScale() + (int)pos.y - rc.size.height;

	return rc;
}

//アクション矩形情報取得
const std::vector<ActionRect>& CharacterObject::GetActionRects() const
{
	return _actionData.actInfo.at(_nowName).cuts[_nowCutIdx].actrects;
}

//キャラの座標を返す
const Position2f & CharacterObject::GetPos() const
{
	return _pos;
}

//アクションデータコピー
void CharacterObject::Copy(const CharacterObject & c)
{
	_actionData.imgFilePath = c._actionData.imgFilePath;
	for (auto& info : c._actionData.actInfo){
		_actionData.actInfo[info.first] = info.second;
	}

	_isTurn = c._isTurn;
	_pos = c._pos;
	_nowName = c._nowName;
	_nowCutIdx = c._nowCutIdx;
	_frame = c._frame;
}

CharacterObject::CharacterObject(const Camera & c) :_frame(0), _nowCutIdx(0), _camera(c)
{
}

CharacterObject::~CharacterObject()
{
}
