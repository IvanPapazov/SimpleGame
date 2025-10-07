#include "playerObject.h"
#include "loadTexture.h"
#include "RenderingManager.h"

RenderingManager& rendererManager = RenderingManager::getInstance();
void blit(SDL_Texture* texture, float x, float y, float w, float h)
{
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	dest.w = w;
	dest.h = h;

	SDL_QueryTexture(texture, NULL, NULL, NULL, NULL);
	SDL_RenderCopy(rendererManager.getRenderer(), texture, NULL, &dest);
}

