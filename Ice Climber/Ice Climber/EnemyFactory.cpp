#include "EnemyFactory.h"
#include "Topi.h"
#include "Nitpicker.h"
#include "Camera.h"

///“G‚ÌƒIƒŠƒWƒiƒ‹
std::map<std::string, Enemy*>_originalEnemy;

EnemyFactory::EnemyFactory(const Camera& c, const Player& p, const Ground& g) : player(p), ground(g), _camera(c)
{
	_originalEnemy["Topi"] = new Topi(_camera, player, ground);
	_originalEnemy["Nitpicker"] = new Nitpicker(_camera, player, ground);
}


EnemyFactory::~EnemyFactory()
{
}

Enemy * EnemyFactory::Create(const char * enemyname, const Position2f& p)
{
	if (_originalEnemy.find(enemyname) != _originalEnemy.end()) {
		auto enemy = _originalEnemy[enemyname]->Clone();
		enemy->_pos = p;
		_legion.push_back(enemy);
		return enemy;
	}
	else {
		return nullptr;
	}
}

Legion & EnemyFactory::GetLegion()
{
	return _legion;
}
