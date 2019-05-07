#pragma once
#include "CharacterObject.h"

class EnemyFactory;
class Player;
class Ground;
class Camera;

class Enemy :
	public CharacterObject
{
protected:
	const Player& _player;
	const Ground& _ground;

	friend EnemyFactory;
	virtual Enemy* Clone() = 0;
	Enemy(const Camera& c, const Player& p, const Ground& g);
public:
	virtual ~Enemy();
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void OnDamage() = 0;
	virtual void OnGround(int groundline) = 0;
};
