#include <SDL.h>
#include <SDL_image.h>
#include "RenderingManager.h"

SDL_Texture* loadTexture(const char* filePath)
{
	RenderingManager& rendererManager = RenderingManager::getInstance();
	SDL_Texture* texture;
	SDL_Surface* loadedSurface = IMG_Load(filePath);
	texture = SDL_CreateTextureFromSurface(rendererManager.getRenderer(), loadedSurface);

	return texture;
}