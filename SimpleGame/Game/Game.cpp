#include "stdafx.h"
#include "Game.h"
#include "iostream"
#include <Core/GameObjectManager.h>
#include <Utils/ReadInfo.h>
#include <Components/RenderComponent.h>

Game& Game::getInstance()
{
    static Game ms_Instance;
    return ms_Instance;
}

bool Game::IsInitialized()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        m_IsRunning = false;
        return false;
    }

    m_Window = SDL_CreateWindow("Tutorial", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, g_ScreenWidth, g_ScreenHeight, SDL_WINDOW_SHOWN);
    if (m_Window == NULL)
    {
        std::cerr << "m_Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        m_IsRunning = false;
        return false;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
    if (m_Renderer == NULL)
    {
        std::cerr << "m_Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        m_IsRunning = false;
        return false;
    }

    m_IsRunning = true;
    return true;
}

void Game::Shutdown()
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

    SDL_Quit();
}

void Game::Run()
{
    GameObjectManager& gameObjectManager = GameObjectManager::getInstance();
    //SystemManager m_SystemManager;
    ReadInfo info;


    auto terrains = info.ReadInfoTerrain();
    for (auto& [key, object] : terrains) {
        gameObjectManager.AddGameObject(object);
    }
    auto players = info.ReadInfoPlayer();
    for (auto& [key, object] : players) {
        gameObjectManager.AddGameObject(object);
    }
    auto enemies = info.ReadInfoEnemy();
    for (auto& [key, object] : enemies) {
        gameObjectManager.AddGameObject(object);
    }
    while (m_IsRunning) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                m_IsRunning = false;
            }
        }

        SDL_RenderClear(m_Renderer);
        RenderComponent* render;
        if (render->GetOffScreenCombinedTexture())
       {
           SDL_Rect dst = { 0, 0, 1200, 1000 };
           SDL_RenderCopy(m_Renderer, render->GetOffScreenCombinedTexture(), NULL, &dst);
       }
        gameObjectManager.UpdateAllGameObject();
        
        SDL_RenderPresent(m_Renderer);
    }
}