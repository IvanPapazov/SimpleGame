#include "stdafx.h"
#include <SDL.h>
#include <iostream>
#include <systemOld/RenderingManager.h>

RenderingManager& RenderingManager::getInstance()
{
    static RenderingManager ms_Instance;
    return ms_Instance;
}

bool RenderingManager::IsInitialized()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    m_Window = SDL_CreateWindow("Tutorial", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, g_ScreenWidth, g_ScreenHeight, SDL_WINDOW_SHOWN);
    if (m_Window == NULL)
    {
        std::cerr << "m_Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
    if (m_Renderer == NULL)
    {
        std::cerr << "m_Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void RenderingManager::Close()
{
    if (m_Renderer)
    {
        SDL_DestroyRenderer(m_Renderer);
        m_Renderer = NULL;
    }

    if (m_Window)
    {
        SDL_DestroyWindow(m_Window);
        m_Window = NULL;
    }
}
