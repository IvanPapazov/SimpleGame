#pragma once
#include "stdafx.h"
#include <memory>
#include <SDL.h>
#include "Core/QuadTree.h"

#include <Events/EventSystem.h>
#include <Utils/ReadInfo.h>

const int g_ScreenHeight = 1000;
const int g_ScreenWidth = 1200;

class Game
{
private:
    bool m_IsRunning = false;
    std::string m_RequestedLevel;
    bool m_LevelChangeRequested = false;
    std::string m_PreviousLevel = "level_1";
    std::string m_CurrentLevel = "level_1";

    std::unique_ptr<QuadTree> qt;

    Uint64 m_LastFrameTime;
    float m_dt;

    SDL_Window* m_Window = nullptr;
    SDL_Renderer* m_Renderer = nullptr;
    ReadInfo m_Info;

public:
    static Game& getInstance();

    SDL_Renderer* GetRenderer() const { return m_Renderer; }
    SDL_Window* GetWindow() const { return m_Window; }

    QuadTree* GetQuadTree() const { return qt.get(); }
    void SetQuadTree(std::unique_ptr<QuadTree> newQT) { qt = std::move(newQT); }
    const std::string& getPreviousLevel() const { return m_PreviousLevel; }
    void setPreviousLevel(const std::string& levelName) { m_PreviousLevel = levelName; }

    const std::string& getCurrentLevel() const { return m_CurrentLevel; }
    void setCurrentLevel(const std::string& levelName) { m_CurrentLevel = levelName; }

    float GetDeltaTime() const { return m_dt; }

    bool IsInitialized();
    void Run();
    void Shutdown();
    void LoadLevel(const std::string& levelName);
    void RequestLevelChange(const std::string& levelName);


    Game() = default;
    ~Game() = default;
    Game(const Game& g) = delete;
    Game(Game&& g) = delete;
};
