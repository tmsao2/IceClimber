#include "Nitpicker.h"
#include "DxLib.h"
#include "Game.h"
#include "Player.h"
#include "Ground.h"



Nitpicker::Nitpicker(const Camera & c, const Player & p, const Ground & g):Enemy(c, p, g)
{
	readActfile("Action/Nitpicker.act");
	_grapH = LoadGraph(_actionData.imgFilePath.c_str());
	_nowName = "Fly";
	_isTurn = true;
	_frame = 0;
	_updater = &Nitpicker::NeutralUpdate;
}

Nitpicker::Nitpicker(const Nitpicker & n) : Enemy(n._camera, n._player, n._ground)
{
	*this = n;
}

void Nitpicker::operator=(const Nitpicker & n)
{
	this->Copy(n);
	_updater = n._updater;
	_vel = n._vel;
	_grapH = n._grapH;
}

Enemy * Nitpicker::Clone()
{
	return new Nitpicker(*this);
}

Nitpicker::~Nitpicker()
{
}

void Nitpicker::Update()
{
	(this->*_updater)();
	_pos += _vel;
}

void Nitpicker::Draw()
{
	CharacterObject::Draw(_grapH);
}

void Nitpicker::OnGround(int groundline)
{

}

void Nitpicker::OnDamage()
{
	_vel.x = 0;
	ChangeAction("Damage");
	_updater = &Nitpicker::DamageUpdate;
}

void Nitpicker::NeutralUpdate()
{
	if (abs(_player.GetPos().x - _pos.x) < 200) {
		ChangeAction("Fly");
		fly = 0;
		_updater = &Nitpicker::DescentUpdate;
	}
	_isTurn = _player.GetPos().x < _pos.x;
}

void Nitpicker::FlyUpdate()
{
	ProceedAnimationFrame();
	_vel.y = -sin(3.14f * 2.0f / 90.0f * fly) * 4.0f;
	fly += 1.0f;
	if (_isTurn) {
		_vel.x = -2;
	}
	else {
		_vel.x = 2;
	}
}

void Nitpicker::DescentUpdate()
{
	if ((_player.GetPos().y - 100) < _pos.y) {
		_updater = &Nitpicker::FlyUpdate;
		_isTurn = _player.GetPos().x < _pos.x;
	}
	else {
		ProceedAnimationFrame();
		_vel.y = 3;
		_isTurn = _player.GetPos().x < _pos.x;
	}
}

void Nitpicker::DamageUpdate()
{
	Game& game = Game::Instance();

	ProceedAnimationFrame();
	_vel.x = 0;
	_vel.y += game.GetGravity();
}

void Nitpicker::DieUpdate()
{

}

void Nitpicker::RevivalUpdate()
{
}
