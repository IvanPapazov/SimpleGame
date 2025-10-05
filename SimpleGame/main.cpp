#include <SDL.h>
#include <iostream>
#include "window.h"
#include "playerObject.h"
#include "loadTexture.h"

const int GROUND_HEIGHT = 50;

int main(int argc, char* argv[]) {
    memset(&app, 0, sizeof(App));
    memset(&player, 0, sizeof(Entity));
    memset(&ground, 0, sizeof(Entity));

    if (!init()) {
        std::cerr << "Failed to initialize!\n";
        return 1;
    }

    player.x = 100;
    player.y = 200;
    player.w = 80;
    player.h = 100;
    player.texture = loadTexture("images/preview.png");
    if (!player.texture) {
        std::cerr << "Failed to load player texture!\n";
        close();
        return 1;
    }

    ground.x = 0;
    ground.y = GROUND_HEIGHT;
    ground.w = SCREEN_WIDTH;
    ground.h = SCREEN_HEIGHT;
    ground.texture = loadTexture("images/ground.png");
    if (!ground.texture) {
        std::cerr << "Failed to load player texture!\n";
        close();
        return 1;
    }
    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        SDL_SetRenderDrawColor(app.renderer, 135, 206, 235, 255);
        SDL_RenderClear(app.renderer);

        blit(ground.texture, ground.x, ground.y, ground.w, ground.h);
        gra
        SDL_RenderPresent(app.renderer);
    }

    close();
    return 0;
}