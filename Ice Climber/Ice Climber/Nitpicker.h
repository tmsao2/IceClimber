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
	int _grapH; //画像ハンドル
	float fly;

	//メンバ関数ポインタ
	void (Nitpicker::*_updater)();
	//状態（ステート）
	//ニュートラル
	void NeutralUpdate();
	//飛行
	void FlyUpdate();
	//降下
	void DescentUpdate();
	//ダメージ
	void DamageUpdate();
	//死亡
	void DieUpdate();
	//復活
	void RevivalUpdate();

	friend EnemyFactory;
	Nitpicker(const Camera& c, const Player& p, const Ground& g);
	Nitpicker(const Nitpicker&);//コピー禁止
	void operator=(const Nitpicker&);//代入禁止
	Enemy* Clone();

public:
	~Nitpicker();
	void Update();
	void Draw();
	void OnGround(int groundline);
	void OnDamage();
};
