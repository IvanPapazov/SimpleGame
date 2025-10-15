#include "stdafx.h"
#include <SDL.h>
#include <iostream>
#include "RenderingManager.h"
#include <unordered_map> 
#include <GameObject.h>
#include "system/GameObjectFactory.h"
#include "Components/JumpComponent.h"
#include <Components/MoveLeftRightComponent.h>
#include "Components/GravityComponent.h"
#include "Components/FireBulletComponent.h"
#include <Components/DrawComponent.h>
#include <GameObjectManager.h>

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
	GameObjectFactory m_ComponentManager;
	GameObjectManager m_gameObjectManager;
	std::unordered_map<std::string, Components*> m_Componets = m_ComponentManager.ReadInfo(ms_RendererManager);
	while (m_IsRunning)
	{
		SDL_RenderClear(ms_RendererManager.GetRenderer());
		SDL_SetRenderDrawColor(ms_RendererManager.GetRenderer(), 135, 206, 235, 255);
		m_gameObjectManager.UpdateComponents();


		while (SDL_PollEvent(&m_Event))
		{
			if (m_Event.type == SDL_QUIT)
			{
				m_IsRunning = false;
			}
			if (m_Event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (m_Event.button.button == SDL_BUTTON_LEFT)
				{
					float mouseX;
					float mouseY;
					mouseX = m_Event.button.x;
					mouseY = m_Event.button.y;
					m_gameObjectManager.HandleAllEvents(mouseX, mouseY);
				}
			}
			if (m_Event.type == SDL_KEYDOWN)
			{
				m_gameObjectManager.CreateGameObject(m_Componets);
			}
		}
		SDL_RenderPresent(ms_RendererManager.GetRenderer());
	}
	ms_RendererManager.Close();
	return 0;
}