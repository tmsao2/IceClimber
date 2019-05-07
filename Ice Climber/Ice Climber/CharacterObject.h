#pragma once
#include <string>
#include <map>
#include <vector>
#include "Geometry.h"

class Camera;

enum class RectType {
	anchor,
	attack,
	damage
};

struct ActionRect {
	RectType rt;//アクションタイプ
	Rect rc;//アクション矩形
};

///切り抜き情報
struct CutInfo {
	Rect rc;//切り抜き矩形
	Position2 center; //中心点
	int duration;//表示時間
	std::vector<ActionRect> actrects;
};//28バイト+16バイト
typedef std::vector<CutInfo> CutInfoes_t;

struct  ActionInfo {
	bool isLoop; //ループ情報
	CutInfoes_t cuts; //カット情報配列
};

struct ActionData {
	std::string imgFilePath;//画像ファイルのパス
	std::map<std::string, ActionInfo> actInfo;//アクション情報
};


///キャラクター基底クラス
class CharacterObject
{
protected:
	const Camera& _camera;

	bool _isTurn;

	ActionData _actionData;

	std::string _nowName;//「今」のアクション名
	int _nowCutIdx;//「今」表示中のカット番号
	unsigned int _frame;//そのカット番号における経過フレーム

	//アニメーションの変更
	void ChangeAction(const char* name);
	//アニメーションのフレームを1進める
	bool ProceedAnimationFrame();
	//アクションデータ読み込み
	void readActfile(const char* actionPath);

	//キャラの描画
	void Draw(int& Img);
	void DebugDraw();

public:
	Position2f _pos;

	///矩形の表示場所
	Rect GetActuralRectForAction(const Rect& _rec) const;

	const std::vector<ActionRect>& GetActionRects() const;
	const Position2f& GetPos() const;

	void Copy(const CharacterObject& c);

	CharacterObject(const Camera& c);
	virtual ~CharacterObject();
};

