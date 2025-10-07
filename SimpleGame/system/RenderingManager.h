#pragma once
#include <SDL.h>
#include <iostream>
#include <unordered_map>
#include <GameObject.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

class RenderingManager
{
public:
    static RenderingManager& getInstance();

    bool init();
    void close();
    void addGameObject(GameObject* gameObject);

    SDL_Renderer* getRenderer() const { return renderer; }
    SDL_Window* getWindow() const { return window; }

private:
    RenderingManager() = default;
    ~RenderingManager() = default;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    std::unordered_map<int, GameObject*> gameObjects;
};