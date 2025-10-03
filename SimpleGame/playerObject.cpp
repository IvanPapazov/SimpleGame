#include "window.h"
#include "playerObject.h"

Entity player;
Entity ground;

void blit(SDL_Texture* texture, int x, int y, int w, int h)
{
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;
	dest.w = w;
	dest.h = h;

	SDL_QueryTexture(texture, NULL, NULL, NULL, NULL);

	SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}