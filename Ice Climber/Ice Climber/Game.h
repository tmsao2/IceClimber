#pragma once
#include <memory>
#include "Geometry.h"

class Scene;

//�Q�[���S�̂𐧌䂷��N���X

class Game
{
private:
	Game();					//�����֎~
	Game(const Game&);		//�R�s�[�֎~
	void operator=(const Game&)const;	//����֎~

	///�V�[���Ǘ�
	std::shared_ptr<Scene> _scene;
public:
	Size screen_size;

	static Game& Instance() {
		static Game instance;
		return instance;
	}
	~Game();

	///�L�����N�^�[�̊g�嗦��Ԃ�
	float GetObjectScale()const;
	///�d�͂�Ԃ�
	float GetGravity() const;
	///�E�B���h�E�̃T�C�Y
	const Size GetWindowSize() const;

	///�������n
	void Initialize();

	///���Ƀ��[�v
	void Run();

	///�㏈��
	void Terminate();

	///�V�[���̕ύX
	void ChangeScene(Scene* scene);
};

