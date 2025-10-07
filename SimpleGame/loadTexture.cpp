#include <SDL.h>
#include <SDL_image.h>
#include "RenderingManager.h"

SDL_Texture* LoadTexture(const char* filePath)
{
	RenderingManager& rendererManager = RenderingManager::getInstance();
	SDL_Texture* m_Texture;
	SDL_Surface* m_LoadedSurface = IMG_Load(filePath);
	m_Texture = SDL_CreateTextureFromSurface(rendererManager.GetRenderer(), m_LoadedSurface);

	return m_Texture;
}