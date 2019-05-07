#include "Topi.h"
#include "DxLib.h"
#include "Game.h"
#include "Player.h"
#include "Ground.h"


Topi::Topi(const Camera & c, const Player & p, const Ground & g):Enemy(c,p,g)
{
	readActfile("Action/Topi.act");
	_grapH = LoadGraph(_actionData.imgFilePath.c_str());
	_nowName = "Walk";
	_isTurn = true;
	_frame = 0;
	_pos.x = 256;
	_pos.y = 1400;
	_updater = &Topi::NeutralUpdate;
}

Topi::Topi(const Topi & t) : Enemy(t._camera, t._player, t._ground)
{
	*this = t;
}

void Topi::operator=(const Topi & t)
{
	this->Copy(t);
	_updater = t._updater;
	_vel = t._vel;
	_grapH = t._grapH;
}

Enemy * Topi::Clone()
{
	return new Topi(*this);
}

Topi::~Topi()
{
}

void Topi::Update()
{
	(this->*_updater)();
	_pos += _vel;
	_vel.y += Game::Instance().GetGravity();
}

void Topi::Draw()
{
	CharacterObject::Draw(_grapH);
}

void Topi::OnGround(int groundline)
{
	_vel.y = 0;
	_pos.y = groundline;
}

void Topi::OnDamage()
{
	ChangeAction("Damage");
	_vel.x = _isTurn ? -1 : 1;
	_updater = &Topi::DamageUpdate;
}

void Topi::NeutralUpdate()
{
	_isTurn = _player.GetPos().x < _pos.x;
	_updater = &Topi::WalkUpdate;
	_wait = 60;
}

void Topi::WalkUpdate()
{
	if (_wait > 0) {
		--_wait;
		ProceedAnimationFrame();
	}
	else {
		_updater = &Topi::NeutralUpdate;
	}

	_vel.x = _isTurn ? -1 : 1;
}

void Topi::DamageUpdate()
{
	ProceedAnimationFrame();

}

void Topi::DieUpdate()
{
}

void Topi::RevivalUpdate()
{
}
