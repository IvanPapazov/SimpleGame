#include "playerObject.h"
#include "LoadTexture.h"
#include "RenderingManager.h"

RenderingManager& ms_RendererManager = RenderingManager::getInstance();
void Blit(SDL_Texture* texture, float x, float y, float w, float h)
{
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	dest.w = w;
	dest.h = h;

	SDL_QueryTexture(texture, NULL, NULL, NULL, NULL);
	SDL_RenderCopy(ms_RendererManager.GetRenderer(), texture, NULL, &dest);
}

