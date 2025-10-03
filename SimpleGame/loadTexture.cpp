#include <SDL.h>
#include <SDL_image.h>
#include "window.h"

SDL_Texture* loadTexture(const char* filePath)
{
	SDL_Texture* texture;
	SDL_Surface* loadedSurface = IMG_Load(filePath);
	texture = SDL_CreateTextureFromSurface(app.renderer, loadedSurface);

	return texture;
}