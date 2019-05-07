#include "Game.h"
#include "DxLib.h"
#include "Peripheral.h"
#include "Scene.h"
#include "TitleScene.h"
#include <memory>

const int screen_x_size = 512;
const int screen_y_size = 480;

Game::Game()
{
	screen_size.width = screen_x_size;
	screen_size.height = screen_y_size;
}

void Game::operator=(const Game &) const
{
}

Game::~Game()
{
}

float Game::GetObjectScale() const
{
	return 2.0f;
}

float Game::GetGravity() const
{
	return 0.4f;
}

const Size Game::GetWindowSize() const
{
	return screen_size;
}

void Game::Initialize()
{
	DxLib::SetGraphMode(screen_x_size, screen_y_size, 32);
	DxLib::SetMainWindowText("1701377_高須真樹_Ice Climber");
	DxLib::ChangeWindowMode(true);
	if (DxLib::DxLib_Init() == -1) {
		return;
	}
	DxLib::SetDrawScreen(DX_SCREEN_BACK);
	ChangeScene(new TitleScene());
}

void Game::Run()
{
	Peripheral peripheral;

	while (ProcessMessage() == 0) {
		if (DxLib::CheckHitKey(KEY_INPUT_ESCAPE)) {
			break;
		}

		DxLib::ClsDrawScreen();

		//入力情報取得
		peripheral.Update();

		//シーン更新
		_scene->Update(peripheral);

		DxLib::ScreenFlip();
	}
}

void Game::Terminate()
{
	DxLib::DxLib_End();
}

void Game::ChangeScene(Scene * scene)
{
	_scene.reset(scene);
}
