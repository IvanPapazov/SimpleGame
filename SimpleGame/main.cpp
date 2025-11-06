#include "stdafx.h"
#include <SDL.h>
#include <Game/Game.h>

Game& game = Game::getInstance();

int main(int argc, char* argv[])
{

	if (!game.IsInitialized()) {
		return -1;
	}

	game.Run();
	game.Shutdown();

	return 0;
}