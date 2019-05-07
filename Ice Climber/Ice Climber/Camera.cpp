#include "Camera.h"
#include <cassert>
#include "Stage.h"
#include "CharacterObject.h"
#include "Game.h"

const int scrSpeed = 6;

Camera::Camera(Stage& s) :_stage(s), _pos(0, 0)
{
	auto& size = Game::Instance().GetWindowSize();
	auto& range = _stage.GetStageRange();//ステージの範囲を取得
	_pos = Position2f(range.center.x, range.Bottom() - size.height / 2);
	scrflag = false;
}


Camera::~Camera()
{
}

const int Camera::ScrollValue() const
{
	auto _tmp = GetViewport();
	auto scroll = _tmp.Top();//上スクロール値算出
	scroll %= (bgimg_y_size + bnimg_y_size + unimg_y_size) * 2;
	return scroll;
}

void Camera::SetFocus(std::shared_ptr<CharacterObject> c)
{
	_focus = c;
}

const Position2f & Camera::GetPosition() const
{
	return _pos;
}

const Rect Camera::GetViewport() const
{
	Game& game = Game::Instance();

	Rect _rcCamera;

	_rcCamera.size = game.GetWindowSize();
	_rcCamera.center.x = (int)_pos.x;
	_rcCamera.center.y = (int)_pos.y;

	return _rcCamera;
}

void Camera::Update()
{
	assert(!_focus.expired());
	auto& range = _stage.GetStageRange();//ステージの範囲を取得
	auto& size = Game::Instance().GetWindowSize();

	if (scrflag&&cnt <= 112) {
		_pos.y -= scrSpeed;
		cnt+=scrSpeed;
	}
	else {
		scrflag = false;
		cnt = 0;
	}

	//カメラ座標の補正
	if (_pos.x - size.width / 2 < range.Left()) {
		_pos.x = (float)range.Left() + (float)size.width / 2.0f;
	}
	else if (_pos.x + size.width / 2 > range.Right()) {
		_pos.x = (float)range.Right() - (float)size.width / 2.0f;
	}
	if (_pos.y + size.height / 2 > size.height) {
		_pos.y = size.height / 2;
	}
	else if (_pos.y  < size.height-range.Bottom()) {
		_pos.y = size.height - range.Bottom();
	}
}

Position2f Camera::CalculatePosition(Position2f pos) const
{
	auto& size = Game::Instance().GetWindowSize();

	auto p = pos;
	p.x = (p.x - _pos.x) + size.width / 2;
	//p.y = (p.y - _pos.y) + size.height / 2;

	return p;
}

void Camera::CheckPos(Position2 pos)
{
	if (pos.y < _pos.y-32) {
		scrflag = true;
	}
}
