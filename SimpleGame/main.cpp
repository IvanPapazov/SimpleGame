#include "stdafx.h"
#include <SDL.h>
#include <iostream>
#include "RenderingManager.h"
#include <unordered_map> 
#include <GameObject.h>
#include "Components/ComponentManager.h"
#include "Components/JumpComponent.h"
#include <Components/MoveLeftRightComponent.h>
#include "Components/GravityComponent.h"
#include "Components/FireBuletComponent.h"

const float g_GroundHeight = 50.0f;
RenderingManager& ms_RendererManager = RenderingManager::getInstance();

int main(int argc, char* argv[])
{
	if (!ms_RendererManager.IsInitialized())
	{
		std::cerr << "Failed to initialize!\n";
		return 1;
	}

	bool moveLeft = false;
	bool moveRight = false;
	bool jump = false;

	GameObject* player = nullptr;
	bool m_IsRunning = true;
	SDL_Event m_Event;
	ComponentManager m_ComponentManager;
	std::vector<GameObject*> players = m_ComponentManager.ReadInfo(ms_RendererManager);
	for (GameObject* player1 : players)
	{
		ms_RendererManager.AddGameObject(player1);
	}
	Uint64 m_Last = SDL_GetPerformanceCounter();
	float deltaTime = 0.0f;
	while (m_IsRunning)
	{
		Uint64 m_Now = SDL_GetPerformanceCounter();
		deltaTime = (float)(m_Now - m_Last) / (float)SDL_GetPerformanceFrequency();
		m_Last = m_Now;

		//std::unordered_map<int, GameObject*> players = ms_RendererManager.GetAllGameObjects();
		SDL_RenderClear(ms_RendererManager.GetRenderer());
		SDL_SetRenderDrawColor(ms_RendererManager.GetRenderer(), 135, 206, 235, 255);
		for (GameObject* playerUpdate : players)
		{
			if (playerUpdate->HasComponent<MoveLeftRightComponent>())
			{
				GravityComponent* gravity = playerUpdate->GetComponent<GravityComponent>();
				gravity->SetDeltaTime(deltaTime);
			}
			playerUpdate->UpdateComponents(playerUpdate);
		}
		SDL_RenderPresent(ms_RendererManager.GetRenderer());


		while (SDL_PollEvent(&m_Event))
		{
			/*m_Last = m_Now;
			m_Now = SDL_GetPerformanceCounter();
			deltaTime = (float)((m_Now - m_Last) * 1000.0f / (float)SDL_GetPerformanceFrequency()) / 1000.0f;*/
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
					case SDLK_ESCAPE:
						m_IsRunning = false;
						break;

					case SDLK_SPACE:
						if (player->HasComponent<FireBuletComponent>() )
						{
							FireBuletComponent* bulet = player->GetComponent<FireBuletComponent>();
							
							bulet->Update();

						}
						break;
					case SDLK_UP:
						if (player->HasComponent<JumpComponent>())
						{
							Components* jump = player->GetComponent<JumpComponent>();
							jump->Update();
						}
						break;

					case SDLK_LEFT:
						if (player->HasComponent<MoveLeftRightComponent>())
						{
							MoveLeftRightComponent* move = player->GetComponent<MoveLeftRightComponent>();
							move->SetDeltaTime(-deltaTime);
							move->Update();
						}
						break;

					case SDLK_RIGHT:
						if (player->HasComponent<MoveLeftRightComponent>())
						{
							MoveLeftRightComponent* move = player->GetComponent<MoveLeftRightComponent>();
							move->SetDeltaTime(deltaTime);
							move->Update();
						}
						break;
					}
				}
				else
				{
					if (player->HasComponent<MoveLeftRightComponent>())
					{
						MoveLeftRightComponent* move = player->GetComponent<MoveLeftRightComponent>();
						move->SetDeltaTime(0.0f);
						move->Update();
					}
				}
			}
		}
	}
	delete player;
	ms_RendererManager.Close();
	return 0;
}