#include "Enemy.h"




Enemy::Enemy(const Camera & c, const Player & p, const Ground & g) : CharacterObject(c), _player(p), _ground(g)
{
}

Enemy::~Enemy()
{
}
