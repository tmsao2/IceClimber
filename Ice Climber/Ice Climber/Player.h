#pragma once
#include "CharacterObject.h"

class Game;
class Peripheral;
class Camera;

class Player :
	public CharacterObject
{
	friend Game;
private:

	
	Vector2f _vel;
	int _life;
	int _ultimateTime;
	int _playerImg;

	bool _isDie;	//死亡フラグ
	bool _isAerial;	//空中フラグ
	bool _isFall;	//落下フラグ

	void Jump();
	void Attack();

	//メンバ関数ポインタ
	void (Player::*_updater)(const Peripheral&);

	//アクションの状態
	//ニュートラル
	void NeutralUpdate(const Peripheral& p);
	//歩く
	void WalkUpdate(const Peripheral& p);
	//ジャンプ
	void JumpUpdate(const Peripheral& p);
	//攻撃
	void AttackUpdate(const Peripheral& p);
	//着地
	void GroundUpdate(const Peripheral& p);
	//ダメージ
	void DamageUpdate(const Peripheral& p);
	//死亡
	void DieUpdate(const Peripheral& p);
	//落下
	void FallUpdate(const Peripheral& p);

public:
	Player(const Camera& c);
	~Player();

	void Update(const Peripheral& p);
	void Draw();
	void OnGround(int groundline);
	void OnDamage();
	void HitBlock(Rect rec);
	void Fall();
	bool GetFall();
	int GetLife() const;
	bool Die() const;
	bool GetTurn() const;
};

