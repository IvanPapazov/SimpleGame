#include "stdafx.h"
#include <SDL.h>
#include <Game/Game.h>


int main(int argc, char* argv[])
{

	//	SDL_SetRenderDrawColor(ms_RendererManager.GetRenderer(), 135, 206, 235, 255);


	Game& game = Game::getInstance();

	if (!game.IsInitialized()) {
		return -1;
	}

	game.Run();
	game.Shutdown();

	return 0;
}