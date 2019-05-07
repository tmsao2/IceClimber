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

	bool _isDie;	//���S�t���O
	bool _isAerial;	//�󒆃t���O
	bool _isFall;	//�����t���O

	void Jump();
	void Attack();

	//�����o�֐��|�C���^
	void (Player::*_updater)(const Peripheral&);

	//�A�N�V�����̏��
	//�j���[�g����
	void NeutralUpdate(const Peripheral& p);
	//����
	void WalkUpdate(const Peripheral& p);
	//�W�����v
	void JumpUpdate(const Peripheral& p);
	//�U��
	void AttackUpdate(const Peripheral& p);
	//���n
	void GroundUpdate(const Peripheral& p);
	//�_���[�W
	void DamageUpdate(const Peripheral& p);
	//���S
	void DieUpdate(const Peripheral& p);
	//����
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

