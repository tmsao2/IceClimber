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

	///�t�H�[�J�X���ׂ��L�����N�^�[�I�u�W�F�N�g���Z�b�g
	void  SetFocus(std::shared_ptr<CharacterObject> c);

	///�J�����̍��W��Ԃ�
	const Position2f& GetPosition()const;

	///���݌����Ă���͈͂�Ԃ�
	const Rect GetViewport()const;

	void Update();

	Position2f CalculatePosition(Position2f pos)const;

	void CheckPos(Position2 pos);

	const int ScrollValue()const;
};

