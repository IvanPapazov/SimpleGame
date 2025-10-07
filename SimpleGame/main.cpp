#include <SDL.h>
#include <iostream>
#include "playerObject.h"
#include "LoadTexture.h"
#include "RenderingManager.h"
#include <unordered_map> 
#include <GameObject.h>

const float g_GroundHeight = 50.0f;


int main(int argc, char* argv[]) {

	RenderingManager& ms_RendererManager = RenderingManager::getInstance();

	if (!ms_RendererManager.m_IsInitialized()) {
		std::cerr << "Failed to initialize!\n";
		return 1;
	}

	bool m_IsRunning = true;
	SDL_Event m_Event;
	Uint64 m_Now = SDL_GetPerformanceCounter();
	Uint64 m_Last = 0;
	float m_DeltaTime = 0;
	float mouseX;
	float mouseY;

	GameObject* m_Player1 = InitializeGameObject(100.0f, 100.0f, 80.0f, 100.0f, "images/preview.png");
	ms_RendererManager.AddGameObject(m_Player1);
	GameObject* m_Player2 = InitializeGameObject(250.0f, 300.0f, 80.0f, 100.0f, "images/preview.png");
	ms_RendererManager.AddGameObject(m_Player2);
	GameObject* m_Player3 = InitializeGameObject(400.0f, 200.0f, 80.0f, 100.0f, "images/preview.png");
	ms_RendererManager.AddGameObject(m_Player3);

	while (m_IsRunning) {
		GameObject* player = nullptr;

		while (SDL_PollEvent(&m_Event)) {
			if (m_Event.type == SDL_QUIT) {
				m_IsRunning = false;
			}
			if (m_Event.type == SDL_KEYDOWN) {
				if (m_Event.key.keysym.sym == SDLK_SPACE) {
					if (player != nullptr) {
						player->GetRigidBody().ApplyJumpForce(player, m_DeltaTime);
					}
				}
			}
			if (m_Event.type == SDL_MOUSEBUTTONDOWN) {
				if (m_Event.button.button == SDL_BUTTON_LEFT) {
					mouseX = m_Event.button.x;
					mouseY = m_Event.button.y;
					player = SelectGameObjectAt(mouseX, mouseY, ms_RendererManager.GetAllGameObjects());
				}
			}
		}

		SDL_SetRenderDrawColor(ms_RendererManager.GetRenderer(), 135, 206, 235, 255);
		SDL_RenderClear(ms_RendererManager.GetRenderer());


		m_Last = m_Now;
		m_Now = SDL_GetPerformanceCounter();
		m_DeltaTime = (float)((m_Now - m_Last) * 1000.0f / (float)SDL_GetPerformanceFrequency()) / 1000.0f;

		for (auto& element : ms_RendererManager.GetAllGameObjects()) {
			RigidBody m_RigidBody = element.second->GetRigidBody();
			m_RigidBody.ApplyGravityForce(element.second, m_DeltaTime);
			m_RigidBody.Update(m_DeltaTime);
			Blit(element.second->GetTexture(), m_RigidBody.GetPosition().x, m_RigidBody.GetPosition().y, element.second->GetWidth(), element.second->GetHeight());
		}


		SDL_RenderPresent(ms_RendererManager.GetRenderer());
	}
	for (auto& element : ms_RendererManager.GetAllGameObjects()) {
		delete element.second;
	}
	ms_RendererManager.Close();
	return 0;
}