#include "Pch.h"
#include "Core.h"
#include "Game.h"

int __stdcall WinMain(void* hInstance, void* hPrevInstance, char* lpCmdLine, int nShowCmd)
{
	Game* game = new Game;
	game->Go();
	delete game;
	return 0;
}
