#pragma once
#include "Enemy.h"

class Player;
class EnemyFactory;
class Ground;

class Topi :
	public Enemy
{
private:
	Vector2f _vel;
	int _wait;
	int _grapH; //�摜�n���h��

	//�����o�֐��|�C���^
	void (Topi::*_updater)();
	//��ԁi�X�e�[�g�j
	//�j���[�g����
	void NeutralUpdate();
	//����
	void WalkUpdate();
	//�_���[�W
	void DamageUpdate();
	//���S
	void DieUpdate();
	//����
	void RevivalUpdate();

	friend EnemyFactory;
	Topi(const Camera& c, const Player& p, const Ground& g);
	Topi(const Topi&);//�R�s�[�֎~
	void operator=(const Topi&);//����֎~
	Enemy* Clone();

public:
	~Topi();
	void Update();
	void Draw();
	void OnGround(int groundline);
	void OnDamage();
};
