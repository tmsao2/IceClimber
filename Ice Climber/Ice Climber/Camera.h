#pragma once
#include <memory>
#include "Geometry.h"

class CharacterObject;
class Stage;

const int bgimg_y_size = 384;
const int bnimg_y_size = 368;
const int unimg_y_size = 16;

class Camera
{
private:
	std::weak_ptr<CharacterObject> _focus;
	Position2f _pos;
	Stage& _stage;
	bool scrflag;
	int cnt = 0;
public:
	Camera(Stage& s);
	~Camera();

	///フォーカスすべきキャラクターオブジェクトをセット
	void  SetFocus(std::shared_ptr<CharacterObject> c);

	///カメラの座標を返す
	const Position2f& GetPosition()const;

	///現在見えている範囲を返す
	const Rect GetViewport()const;

	void Update();

	Position2f CalculatePosition(Position2f pos)const;

	void CheckPos(Position2 pos);

	const int ScrollValue()const;
};

