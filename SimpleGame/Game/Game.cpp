#include "stdafx.h"
#include "Game.h"
#include <iostream>
#include <Core/GameObjectManager.h>
#include <Components/RenderComponent.h>
#include <Core/ResourceManager.h>
#include <Core/QuadTree.h>
#include <Events/EventHandler.h>

GameObjectManager& gameObjectManager = GameObjectManager::getInstance();
EventHandler& g_EventHandler = EventHandler::getInstance();
ResourceManager& g_ResourceManager = ResourceManager::getInstance();

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
    if (!m_Window)
    {
        std::cerr << "Window creation failed! SDL_Error: " << SDL_GetError() << std::endl;
        m_IsRunning = false;
        return false;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
    if (!m_Renderer)
    {
        std::cerr << "Renderer creation failed! SDL_Error: " << SDL_GetError() << std::endl;
        m_IsRunning = false;
        return false;
    }

    Rect worldBounds = { 0, 0, g_ScreenWidth, g_ScreenHeight };
    qt = std::make_unique<QuadTree>(worldBounds);

    m_IsRunning = true;
    return true;
}

void Game::RequestLevelChange(const std::string& levelName) {
    m_RequestedLevel = levelName;
    m_LevelChangeRequested = true;
}

void Game::LoadLevel(const std::string& levelName)
{
    auto terrains = m_Info.ReadInfoTerrain(levelName);
    for (auto& [key, object] : terrains) {
        gameObjectManager.AddGameObject(std::move(object));
    }
    auto pathways = m_Info.ReadInfoPathways(levelName);
    for (auto& [key, object] : pathways) {
        gameObjectManager.AddGameObject(std::move(object));
    }
    auto doors = m_Info.ReadInfoDoors(levelName);
    for (auto& [key, object] : doors) {
        gameObjectManager.AddGameObject(std::move(object));

    }
    auto players = m_Info.ReadInfoPlayer(levelName);
    for (auto& [key, object] : players) {
        gameObjectManager.AddGameObject(std::move(object));
    }
    auto enemies = m_Info.ReadInfoEnemy(levelName);
    for (auto& [key, object] : enemies) {
        gameObjectManager.AddGameObject(std::move(object));

    }
}

void Game::Shutdown()
{
    if (m_Renderer)
    {
        SDL_DestroyRenderer(m_Renderer);
        m_Renderer = nullptr;
    }

    if (m_Window)
    {
        SDL_DestroyWindow(m_Window);
        m_Window = nullptr;
    }

    SDL_Quit();
}

void Game::Run()
{
    m_Info.ReadTextures();
    m_Info.ReadSpriteData();
    LoadLevel("level_1");
    m_LastFrameTime = SDL_GetPerformanceCounter();

    while (m_IsRunning) {
        SDL_Event event;
        std::vector<int> toRemove;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                m_IsRunning = false;
            }
        }

        SDL_RenderClear(m_Renderer);

        Uint64 start = SDL_GetPerformanceCounter();
        Uint64 frameTime = start - m_LastFrameTime;
        m_dt = (frameTime / static_cast<float>(SDL_GetPerformanceFrequency())) * 100.0f;
        m_LastFrameTime = start;

        if (RenderComponent::GetOffScreenCombinedTexture())
        {
            SDL_Rect dst = { 0, 0, g_ScreenWidth, g_ScreenHeight };
            SDL_RenderCopy(m_Renderer, RenderComponent::GetOffScreenCombinedTexture(), nullptr, &dst);
        }

        gameObjectManager.UpdateAllGameObject();

        for (const auto& [key, obj] : gameObjectManager.m_gameObjects) {
            if (obj && !obj->GetIsActive()) {
                g_EventHandler.Unsubscribe(obj.get());
                toRemove.push_back(obj->GetId());
            }
        }
        for (int id : toRemove) {
            gameObjectManager.RemoveGameObject(id);
        }

        if (m_LevelChangeRequested) {
            gameObjectManager.RemoveAllGameObject();
            LoadLevel(m_RequestedLevel);
            m_LevelChangeRequested = false;
        }

        if (qt) {
            qt->Clear();
            for (auto& [key, obj] : gameObjectManager.m_gameObjects) {
                qt->Insert(obj.get());
            }
        }

        SDL_RenderPresent(m_Renderer);
    }
}
