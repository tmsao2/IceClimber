#pragma once
#include <map>
#include <list>
#include "CharacterObject.h"

class Enemy;
class Player;
class Ground;
class Camera;

///“G‚ÌŒR’c
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

	///“G‚Ì–¼‘O
	///¶¬‚³‚ê‚½Enemy‚ğ•Ô‚·‚ª
	///ÀÛ‚É‚Í‹ï‘Ì“I‚È“G(deadman‚È‚Ç)‚ª“ü‚Á‚Ä‚¢‚é
	///‚Â‚Ü‚èƒ|ƒŠƒ‚[ƒtƒBƒYƒ€
	Enemy* Create(const char* enemyname, const Position2f& p);

	///“GW‡‘Ì‚ğ•Ô‚·
	Legion& GetLegion();
};

