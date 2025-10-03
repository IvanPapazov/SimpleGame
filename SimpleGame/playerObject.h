#include <SDL.h>

typedef struct {
    int x;
    int y;
    int w;
    int h;

    float vy;

    SDL_Texture* texture;
} Entity; 

extern Entity player;
extern Entity ground;
void blit(SDL_Texture* texture, int x, int y, int w, int h);
