#include <SDL.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

typedef struct {
    SDL_Renderer* renderer;
    SDL_Window* window;
} App;

extern App app;

bool init();
void close();
