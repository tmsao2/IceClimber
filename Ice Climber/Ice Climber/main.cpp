#include <iostream>
#include <DxLib.h>
#include "Game.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 
{
	Game& game = Game::Instance();
	game.Initialize();
	game.Run();
	game.Terminate();
}