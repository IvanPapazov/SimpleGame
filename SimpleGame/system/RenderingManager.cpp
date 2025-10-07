#include <SDL.h>
#include <iostream>
#include <RenderingManager.h>

RenderingManager& RenderingManager::getInstance()
{
    static RenderingManager instance;
    return instance;
}

bool RenderingManager::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("Tutorial", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void RenderingManager::close()
{
    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }

    if (window)
    {
        SDL_DestroyWindow(window);
        window = NULL;
    }
}