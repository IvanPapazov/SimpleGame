#include <SDL.h>
#include <iostream>
#include "RenderingManager.h"
#include <unordered_map> 
#include <GameObject.h>
#include "Components/ComponentManager.h"
#include "Components/JumpComponent.h"

const float g_GroundHeight = 50.0f;
RenderingManager& ms_RendererManager = RenderingManager::getInstance();

int main(int argc, char* argv[])
{
	if (!ms_RendererManager.IsInitialized())
	{
		std::cerr << "Failed to initialize!\n";
		return 1;
	}

	bool m_IsRunning = true;
	SDL_Event m_Event;
	ComponentManager m_ComponentManager;
	GameObject* player = m_ComponentManager.CreateGameObject(ms_RendererManager);

	while (m_IsRunning)
	{
		while (SDL_PollEvent(&m_Event))
		{
			if (m_Event.type == SDL_QUIT)
			{
				m_IsRunning = false;
			}
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
					break;
				/*case SDLK_LEFT:
					player->GetRigidBody().ApplyMovementForce(player, -m_DeltaTime);
					break;
				case SDLK_RIGHT:
					player->GetRigidBody().ApplyMovementForce(player, m_DeltaTime);
					break;*/
				/*case SDLK_DOWN:
					player->GetRigidBody().ApplyMovementForce(player, 0);
					break;*/
				}

			}
			/*if (m_Event.type == SDL_MOUSEBUTTONDOWN)
			{
				float mouseX;
				float mouseY;
				if (m_Event.button.button == SDL_BUTTON_LEFT)
				{
					mouseX = m_Event.button.x;
					mouseY = m_Event.button.y;
					player = SelectGameObjectAt(mouseX, mouseY, ms_RendererManager.GetAllGameObjects());
				}
			}*/
		}

		SDL_SetRenderDrawColor(ms_RendererManager.GetRenderer(), 135, 206, 235, 255);
		SDL_RenderClear(ms_RendererManager.GetRenderer());

		
		player->UpdateComponents(player);

		SDL_RenderPresent(ms_RendererManager.GetRenderer());
	}
	delete player;
	ms_RendererManager.Close();
	return 0;
}