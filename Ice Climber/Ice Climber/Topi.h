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
	int _grapH; //画像ハンドル

	//メンバ関数ポインタ
	void (Topi::*_updater)();
	//状態（ステート）
	//ニュートラル
	void NeutralUpdate();
	//歩く
	void WalkUpdate();
	//ダメージ
	void DamageUpdate();
	//死亡
	void DieUpdate();
	//復活
	void RevivalUpdate();

	friend EnemyFactory;
	Topi(const Camera& c, const Player& p, const Ground& g);
	Topi(const Topi&);//コピー禁止
	void operator=(const Topi&);//代入禁止
	Enemy* Clone();

public:
	~Topi();
	void Update();
	void Draw();
	void OnGround(int groundline);
	void OnDamage();
};
