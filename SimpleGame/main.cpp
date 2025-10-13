#include "stdafx.h"
#include <SDL.h>
#include <iostream>
#include "RenderingManager.h"
#include <unordered_map> 
#include <GameObject.h>
#include "Components/ComponentManager.h"
#include "Components/JumpComponent.h"
#include <Components/MoveLeftComponent.h>
#include <Components/MoveRightComponent.h>

const float g_GroundHeight = 50.0f;
RenderingManager& ms_RendererManager = RenderingManager::getInstance();

int main(int argc, char* argv[])
{
	if (!ms_RendererManager.IsInitialized())
	{
		std::cerr << "Failed to initialize!\n";
		return 1;
	}

	GameObject* player = nullptr;
	bool m_IsRunning = true;
	SDL_Event m_Event;
	ComponentManager m_ComponentManager;
	std::vector<GameObject*> players = m_ComponentManager.ReadInfo(ms_RendererManager);
	for (GameObject* player1 : players)
	{
		ms_RendererManager.AddGameObject(player1);
	}
	/*Uint64 m_Now = SDL_GetPerformanceCounter();
	Uint64 m_Last = 0;*/
	while (m_IsRunning)
	{

		//std::unordered_map<int, GameObject*> players = ms_RendererManager.GetAllGameObjects();
		SDL_RenderClear(ms_RendererManager.GetRenderer());
		for (GameObject* playerUpdate : players)
		{
			playerUpdate->UpdateComponents(playerUpdate);
		}
		SDL_RenderPresent(ms_RendererManager.GetRenderer());


		while (SDL_PollEvent(&m_Event))
		{
			/*m_Last = m_Now;
			m_Now = SDL_GetPerformanceCounter();
			float deltaTime = (float)((m_Now - m_Last) * 1000.0f / (float)SDL_GetPerformanceFrequency()) / 1000.0f;*/
			if (m_Event.type == SDL_QUIT)
			{
				m_IsRunning = false;
			}
			if (m_Event.type == SDL_MOUSEBUTTONDOWN)
			{
				float mouseX;
				float mouseY;
				if (m_Event.button.button == SDL_BUTTON_LEFT)
				{
					mouseX = m_Event.button.x;
					mouseY = m_Event.button.y;
					player = SelectGameObjectAt(mouseX, mouseY, ms_RendererManager.GetAllGameObjects());
				}
			}
			if (player != nullptr)
			{
				if (m_Event.type == SDL_KEYDOWN)
				{
					switch (m_Event.key.keysym.sym)
					{
					case SDLK_SPACE:
						if (player->HasComponent<JumpComponent>()) {
							Components* jump = player->GetComponent<JumpComponent>();
							jump->Update();
						}
						break;
					case SDLK_UP:
						if (player->HasComponent<JumpComponent>()) {
							Components* jump = player->GetComponent<JumpComponent>();
							jump->Update();
						}
						break;
					case SDLK_LEFT:
						if (player->HasComponent<MoveLeftComponent>()) {
							Components* move = player->GetComponent<MoveLeftComponent>();
							move->Update();
						}
						break;
					case SDLK_RIGHT:
						if (player->HasComponent<MoveRightComponent>()) {
							Components* move = player->GetComponent<MoveRightComponent>();
							move->Update();
						}
						break;
					}
				}
			}
		}
		//SDL_SetRenderDrawColor(ms_RendererManager.GetRenderer(), 135, 206, 235, 255);
		
		
	}
	delete player;
	ms_RendererManager.Close();
	return 0;
}