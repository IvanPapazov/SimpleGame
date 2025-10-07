#pragma once
#include <SDL.h>
#include <iostream>
#include <unordered_map>
#include <GameObject.h>

const int g_ScreenWidth = 800;
const int g_ScreenHeight = 600;

class RenderingManager
{
public:
    static RenderingManager& getInstance();

    bool m_IsInitialized();
    void Close();
    void AddGameObject(GameObject* gameObject);
    std::unordered_map<int, GameObject*>& GetAllGameObjects();

    SDL_Renderer* GetRenderer() const { return m_Renderer; }
    SDL_Window* GetWindow() const { return m_Window; }

private:
    RenderingManager() = default;
    ~RenderingManager() = default;

    SDL_Window* m_Window = nullptr;
    SDL_Renderer* m_Renderer = nullptr;

    std::unordered_map<int, GameObject*> m_GameObjects;
};