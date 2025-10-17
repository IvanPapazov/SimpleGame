#pragma once
#include <SDL.h>

const int g_ScreenHeight = 1000;
const int g_ScreenWidth = 1200;

class Game
{
private:
	bool m_IsRunning = false;
	SDL_Window* m_Window = nullptr;
	SDL_Renderer* m_Renderer = nullptr;
public:
	static Game& getInstance();

	bool IsInitialized();
	void Run();
	void Shutdown();

	Game() = default;
	~Game() = default;
	Game(const Game& rm) = delete;
	Game(Game&& rm) = delete;
};

