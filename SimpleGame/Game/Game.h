#pragma once
#include "stdafx.h"
#include <SDL.h>
#include "Core/QuadTree.h"

const int g_ScreenHeight = 1000;
const int g_ScreenWidth = 1200;

class Game
{
private:
	bool m_IsRunning = false;
	std::string m_RequestedLevel;
	bool m_LevelChangeRequested = false;
	QuadTree* qt;

	Uint64 m_LastFrameTime;
	float m_dt;

	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
public:
	static Game& getInstance();
	SDL_Renderer* GetRenderer() const
	{
		return m_Renderer;
	}
	SDL_Window* GetWindow() const
	{
		return m_Window;
	}
	QuadTree* GetQuadTree() const { return qt; }
	void SetQuadTree(QuadTree* newQT) { qt = newQT; }
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

