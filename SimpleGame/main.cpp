#include "stdafx.h"
#include <SDL.h>
#include <Game/Game.h>
//#include <iostream>
//#include <unordered_map> 
//#include "systemOld/ComponentFactory.h"
//#include "ComponentsOld/JumpComponent.h"
//#include <ComponentsOld/MoveLeftRightComponent.h>
//#include "ComponentsOld/GravityComponent.h"
//#include "ComponentsOld/FireBulletComponent.h"
//#include <ComponentsOld/DrawComponent.h>
//#include <systemOld/GameObjectManager.h>
//#include <systemOld/RenderingManager.h>

//const float g_GroundHeight = 50.0f;
//RenderingManager& ms_RendererManager = RenderingManager::getInstance();

int main(int argc, char* argv[])
{
	//if (!ms_RendererManager.IsInitialized())
	//{
	//	std::cerr << "Failed to initialize!\n";
	//	return 1;
	//}


	//bool m_IsRunning = true;
	//bool m_StartingCheckCollision = false;
	//SDL_Event m_Event;
	//ComponentFactory m_ComponentManager;
	//GameObjectManager m_gameObjectManager;
	//std::unordered_map<int, GameObjectOld*> m_GameObjects = m_ComponentManager.ReadInfo(ms_RendererManager);
	//for (const auto& [id, GameObjectOld] : m_GameObjects) {
	//	m_gameObjectManager.AddGameObject(GameObjectOld);
	//}
	//while (m_IsRunning)
	//{
	//	SDL_RenderClear(ms_RendererManager.GetRenderer());
	//	SDL_SetRenderDrawColor(ms_RendererManager.GetRenderer(), 135, 206, 235, 255);
	//	m_gameObjectManager.UpdateComponents();
	//	if (m_StartingCheckCollision)
	//	{
	//		m_gameObjectManager.CheckCollision();
	//	}

	//	while (SDL_PollEvent(&m_Event))
	//	{
	//		if (m_Event.type == SDL_QUIT)
	//		{
	//			m_IsRunning = false;
	//		}
	//		if (m_Event.type == SDL_MOUSEBUTTONDOWN)
	//		{
	//			if (m_Event.button.button == SDL_BUTTON_LEFT)
	//			{
	//				float mouseX;
	//				float mouseY;
	//				mouseX = m_Event.button.x;
	//				mouseY = m_Event.button.y;
	//				m_gameObjectManager.HandleAllEvents(mouseX, mouseY);
	//				m_StartingCheckCollision = true;
	//			}
	//		}
	//		/*if (m_Event.type == SDL_KEYDOWN)
	//		{*/
	//		//	m_gameObjectManager.AddGameObject()
	//		//}
	//	}
	//	SDL_RenderPresent(ms_RendererManager.GetRenderer());
	//}
	//ms_RendererManager.Close();

	Game game;

	if (!game.IsInitialized()) {
		return -1;
	}

	game.Run();
	game.Shutdown();

	return 0;
}