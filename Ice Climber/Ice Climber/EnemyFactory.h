#pragma once
#include <map>
#include <list>
#include "CharacterObject.h"

class Enemy;
class Player;
class Ground;
class Camera;

///�G�̌R�c
typedef std::list<Enemy*>Legion;

class EnemyFactory
{
private:
	const Player& player;
	const Ground& ground;
	const Camera& _camera;

	Legion _legion;
public:
	EnemyFactory(const Camera& c, const Player& p, const Ground& g);
	~EnemyFactory();

	///�G�̖��O
	///�������ꂽEnemy��Ԃ���
	///���ۂɂ͋�̓I�ȓG(deadman�Ȃ�)�������Ă���
	///�܂�|�����[�t�B�Y��
	Enemy* Create(const char* enemyname, const Position2f& p);

	///�G�W���̂�Ԃ�
	Legion& GetLegion();
};

