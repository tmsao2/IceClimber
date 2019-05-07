#pragma once
#include "Scene.h"
#include "Geometry.h"
#include <memory>
#include <list>

class Peripheral;
class Player;
class BackGround;
class Stage;
class Ground;
class Camera;
class EnemyFactory;

struct BREAK_BLOCK {
	Position2f pos;
	int id;
	Vector2f vel;
	bool turnflag;
	BREAK_BLOCK(Position2f _pos, int _id,Vector2f _vel,bool flag) {
		pos = _pos;
		id = _id;
		vel = _vel;
		turnflag = flag;
	}
};


class GameScene :
	public Scene
{
private:
	std::shared_ptr<Camera> camera;
	std::shared_ptr<Stage> stage;
	std::shared_ptr<Player> player;
	std::shared_ptr<BackGround> background;
	std::shared_ptr<Ground> ground;
	std::shared_ptr<EnemyFactory> efactory;

	std::list<BREAK_BLOCK> br_blocks;

	void (GameScene::*_updater)(const Peripheral&);

	void StartUpdate(const Peripheral& p);

	void NormalUpdate(const Peripheral& p);

	void BonusUpdate(const Peripheral& p);

	float _wait;
	int cnt = 0;

	int blockgh;
	int condorgh;
	int nasugh;
	int gameovergh;
	int blockSize;			//ブロックのサイズ
	int stageheight;		//ステージの高さ
	int stagewidth;			//ステージの幅
	int blockCnt;

	void DebugDraw(Position2 pos);		//ブロックの当たり矩形表示


public:
	GameScene();
	~GameScene();
	void Update(const Peripheral& p);
};

