#pragma once
#include "Enemy.h"

class Player;
class EnemyFactory;
class Ground;

class Nitpicker :
	public Enemy
{
private:
	Vector2f _vel;
	int _wait;
	int _grapH; //�摜�n���h��
	float fly;

	//�����o�֐��|�C���^
	void (Nitpicker::*_updater)();
	//��ԁi�X�e�[�g�j
	//�j���[�g����
	void NeutralUpdate();
	//��s
	void FlyUpdate();
	//�~��
	void DescentUpdate();
	//�_���[�W
	void DamageUpdate();
	//���S
	void DieUpdate();
	//����
	void RevivalUpdate();

	friend EnemyFactory;
	Nitpicker(const Camera& c, const Player& p, const Ground& g);
	Nitpicker(const Nitpicker&);//�R�s�[�֎~
	void operator=(const Nitpicker&);//����֎~
	Enemy* Clone();

public:
	~Nitpicker();
	void Update();
	void Draw();
	void OnGround(int groundline);
	void OnDamage();
};
