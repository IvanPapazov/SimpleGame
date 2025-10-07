#include <SDL.h>
#include <iostream>
#include "playerObject.h"
#include "loadTexture.h"
#include "RenderingManager.h"
#include <GameObject.h>

const int GROUND_HEIGHT = 50;


int main(int argc, char* argv[]) {

    RenderingManager& rendererManager = RenderingManager::getInstance();

    if (!rendererManager.init()) {
        std::cerr << "Failed to initialize!\n";
        return 1;
    }

    //ground.x = 0;
    //ground.y = GROUND_HEIGHT;
    //ground.w = SCREEN_WIDTH;
    //ground.h = SCREEN_HEIGHT;
    //ground.texture = loadTexture("images/ground.png");
    //if (!ground.texture) {
    //    std::cerr << "Failed to load player texture!\n";
    //    close();
    //    return 1;
    //}

    bool running = true;
    SDL_Event event;
    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    float deltaTime = 0;
   
    GameObject player = initializeGameObject(100, 200, "images/preview.png");

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        SDL_SetRenderDrawColor(rendererManager.getRenderer(), 135, 206, 235, 255);
        SDL_RenderClear(rendererManager.getRenderer());
        

        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();
        deltaTime = (float)((NOW - LAST) * 1000.0f / (float)SDL_GetPerformanceFrequency()) / 1000.0f;

        Rigidbody rigidbody = player.getRigidbody();
        rigidbody.applyGravity(player, deltaTime, 9.8f, 400.0f);
        rigidbody.update(deltaTime);
        blit(player.getTexture(), rigidbody.getPosition().x, rigidbody.getPosition().y, player.getWidth(), player.getHeight());
        SDL_RenderPresent(rendererManager.getRenderer());
    }

    rendererManager.close();
    return 0;
}