#include "stdafx.h"
#include <SDL.h>
#include <Game/Game.h>
#include <Events/EventHandler.h>
#include <Core/ResourceManager.h>

Game& game = Game::getInstance();

int main(int argc, char* argv[])
{

	if (!game.IsInitialized()) {
		return -1;
	}

	while (game.RunMainMenu()) {
		game.Run();
		if (!game.IsReturnToMenu()) {
			break;
		}
		game.ResetReturnToMenu();
	}

	game.Shutdown();

	return 0;
}