#pragma once
#include <map>
#include <list>
#include "CharacterObject.h"

class Enemy;
class Player;
class Ground;
class Camera;

///敵の軍団
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

	///敵の名前
	///生成されたEnemyを返すが
	///実際には具体的な敵(deadmanなど)が入っている
	///つまりポリモーフィズム
	Enemy* Create(const char* enemyname, const Position2f& p);

	///敵集合体を返す
	Legion& GetLegion();
};

