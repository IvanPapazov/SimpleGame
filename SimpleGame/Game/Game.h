#pragma once
#include "stdafx.h"
#include <SDL.h>

const int g_ScreenHeight = 1000;
const int g_ScreenWidth = 1200;

class Game
{
private:
	bool m_IsRunning = false;
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

	bool IsInitialized();
	void Run();
	void Shutdown();

	Game() = default;
	~Game() = default;
	Game(const Game& g) = delete;
	Game(Game&& g) = delete;
};

