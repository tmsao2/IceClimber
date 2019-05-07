#include "Player.h"
#include <DxLib.h>
#include <stdio.h>
#include <cassert>
#include "Peripheral.h"
#include "Game.h"
#include "Camera.h"

const char* action_path = "Action/Climber2.act";
const float walk_vel = 4;	//キャラクターの移動速度
const float _ultimateInterval = 4;	//無敵時の点滅間隔

void Player::Jump()
{
	if (!_isAerial) {
		_vel.y -= 10.0f;
		_isAerial = true;
		ChangeAction("Jump 0");
		_updater = &Player::JumpUpdate;
	}
}

void Player::Attack()
{
	ChangeAction("Attack");
	_updater = &Player::AttackUpdate;
}

//状態遷移
//待機
void Player::NeutralUpdate(const Peripheral & p)
{
	if (ProceedAnimationFrame()) {
		ChangeAction("Walk 0");
	}
	if (p.IsPressing(PAD_INPUT_RIGHT)) {
		_isTurn = true;
		_pos.x += walk_vel;
		_updater = &Player::WalkUpdate;
	}
	else if (p.IsPressing(PAD_INPUT_LEFT)) {
		_isTurn = false;
		_pos.x -= walk_vel;
		_updater = &Player::WalkUpdate;
	}
	else {
		ChangeAction("Wait 0");
	}
	if (p.IsPressing(PAD_INPUT_10)) {
		Jump();
	}
	if (p.IsPressing(PAD_INPUT_2)) {
		Attack();
	}
	
}

//歩き
void Player::WalkUpdate(const Peripheral & p)
{
	//アニメーションを再生

	if (p.IsPressing(PAD_INPUT_RIGHT)) {
		_isTurn = true;
		_pos.x += walk_vel;
		_updater = &Player::WalkUpdate;
	}
	else if (p.IsPressing(PAD_INPUT_LEFT)) {
		_isTurn = false;
		_pos.x -= walk_vel;
		_updater = &Player::WalkUpdate;
	}
	else {
		ChangeAction("Walk 0");
		_updater = &Player::NeutralUpdate;
	}
	if (p.IsPressing(PAD_INPUT_10)) {
		Jump();
	}
	if (p.IsPressing(PAD_INPUT_2)) {
		Attack();
	}
	
}

//ジャンプ
void Player::JumpUpdate(const Peripheral & p)
{
	//アニメーションを再生
	ProceedAnimationFrame();

	if (p.IsPressing(PAD_INPUT_RIGHT)) {
		_isTurn = true;
		_pos.x += walk_vel/3;
	}
	else if (p.IsPressing(PAD_INPUT_LEFT)) {
		_isTurn = false;
		_pos.x -= walk_vel/3;
	}
}

//攻撃
void Player::AttackUpdate(const Peripheral & p)
{
	//アニメーションを再生
	if (ProceedAnimationFrame()) {
		ChangeAction("Wait 0");
		_updater = &Player::NeutralUpdate;
	}
}

//着地
void Player::GroundUpdate(const Peripheral & p)
{	
	//アニメーションを再生
	if (ProceedAnimationFrame()) {
		ChangeAction("Wait 0");
	}

	_updater = &Player::NeutralUpdate;
}

//ダメージ
void Player::DamageUpdate(const Peripheral & p)
{
}

//死亡
void Player::DieUpdate(const Peripheral & p)
{
}

void Player::FallUpdate(const Peripheral & p)
{
	ChangeAction("Jump 1");
	//アニメーションを再生
	ProceedAnimationFrame();

	if (p.IsPressing(PAD_INPUT_RIGHT)) {
		_isTurn = true;
		_pos.x += walk_vel / 3;
	}
	else if (p.IsPressing(PAD_INPUT_LEFT)) {
		_isTurn = false;
		_pos.x -= walk_vel / 3;
	}
}


Player::Player(const Camera & c) :CharacterObject(c), _vel(0, 0), _isAerial(true)
{
	_life = 3;
	_ultimateTime = 0;
	_pos.x = 200;
	_pos.y = 200;
	_nowName = "Wait 0";
	_isTurn = false;
	_isDie = false;
	//アクション読み込み
	CharacterObject::readActfile(action_path);
	_playerImg = DxLib::LoadGraph(_actionData.imgFilePath.c_str());
	_updater = &Player::NeutralUpdate;
}

Player::~Player()
{
	DxLib::DeleteGraph(_playerImg);
}

void Player::Update(const Peripheral & p)
{
	Game& game = Game::Instance();

	(this->*_updater)(p);
	_pos += _vel;
	auto right = _camera.GetViewport().Right();
	auto left = _camera.GetViewport().Left();
	_pos.x = min(max(_pos.x, left), right);
	_vel.y += game.GetGravity();
	_isAerial = true;
}

void Player::Draw()
{
	CharacterObject::Draw(_playerImg);
}


void Player::OnGround(int groundline)
{
	_vel.y = 0;
	_pos.y = groundline;
	if (_isAerial) {
		_updater = &Player::NeutralUpdate;
	}
	_isAerial = false;
}

void Player::OnDamage()
{
}

void Player::HitBlock(Rect rec)
{
	_vel.y = 0;
	for (auto prect : Player::GetActionRects()) {
		if (prect.rt == RectType::damage) {
			_pos.y = rec.Bottom() + Player::GetActuralRectForAction(prect.rc).Height();
		}
	}
	_updater = &Player::JumpUpdate;
}

void Player::Fall()
{
	_updater = &Player::FallUpdate;
}

bool Player::GetFall()
{
	if (_vel.y < 0) {
		_isFall = false;
	}
	else
	{
		_isFall = true;
	}
	return _isFall;
}

int Player::GetLife() const
{
	return _life;
}

bool Player::Die() const
{
	return _isDie;
}

bool Player::GetTurn() const
{
	return _isTurn;
}
