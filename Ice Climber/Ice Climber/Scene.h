#pragma once
class Peripheral;
// �V�[���Ǘ��̂��߂̊��N���X
// �������z�N���X
class Scene
{
public:
	Scene();
	virtual ~Scene();

	// �V�[���̍X�V
	virtual void Update(const Peripheral& p) = 0;
};

