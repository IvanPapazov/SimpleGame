#include <SDL.h>
#include <iostream>
#include "window.h"


App app;


void close() {
    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
    app.renderer = nullptr;
    app.window = nullptr;
    SDL_Quit();
}

bool init()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		app.window = SDL_CreateWindow("Tutorial", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (app.window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_ACCELERATED);
			if (app.renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
		}
	}
	return success;
}