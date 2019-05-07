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
	RectType rt;//�A�N�V�����^�C�v
	Rect rc;//�A�N�V������`
};

///�؂蔲�����
struct CutInfo {
	Rect rc;//�؂蔲����`
	Position2 center; //���S�_
	int duration;//�\������
	std::vector<ActionRect> actrects;
};//28�o�C�g+16�o�C�g
typedef std::vector<CutInfo> CutInfoes_t;

struct  ActionInfo {
	bool isLoop; //���[�v���
	CutInfoes_t cuts; //�J�b�g���z��
};

struct ActionData {
	std::string imgFilePath;//�摜�t�@�C���̃p�X
	std::map<std::string, ActionInfo> actInfo;//�A�N�V�������
};


///�L�����N�^�[���N���X
class CharacterObject
{
protected:
	const Camera& _camera;

	bool _isTurn;

	ActionData _actionData;

	std::string _nowName;//�u���v�̃A�N�V������
	int _nowCutIdx;//�u���v�\�����̃J�b�g�ԍ�
	unsigned int _frame;//���̃J�b�g�ԍ��ɂ�����o�߃t���[��

	//�A�j���[�V�����̕ύX
	void ChangeAction(const char* name);
	//�A�j���[�V�����̃t���[����1�i�߂�
	bool ProceedAnimationFrame();
	//�A�N�V�����f�[�^�ǂݍ���
	void readActfile(const char* actionPath);

	//�L�����̕`��
	void Draw(int& Img);
	void DebugDraw();

public:
	Position2f _pos;

	///��`�̕\���ꏊ
	Rect GetActuralRectForAction(const Rect& _rec) const;

	const std::vector<ActionRect>& GetActionRects() const;
	const Position2f& GetPos() const;

	void Copy(const CharacterObject& c);

	CharacterObject(const Camera& c);
	virtual ~CharacterObject();
};

