#include <SDL.h>
#include <iostream>
#include "playerObject.h"
#include "LoadTexture.h"
#include "RenderingManager.h"
#include <GameObject.h>

const int g_GroundHeight = 50;


int main(int argc, char* argv[]) {

    RenderingManager& ms_RendererManager = RenderingManager::getInstance();

    if (!ms_RendererManager.m_IsInitialized()) {
        std::cerr << "Failed to initialize!\n";
        return 1;
    }

    //ground.x = 0;
    //ground.y = g_GroundHeight;
    //ground.w = g_ScreenWidth;
    //ground.h = g_ScreenHeight;
    //ground.texture = LoadTexture("images/ground.png");
    //if (!ground.texture) {
    //    std::cerr << "Failed to load player texture!\n";
    //    Close();
    //    return 1;
    //}

    bool m_IsRunning = true;
    SDL_Event m_Event;
    Uint64 m_Now = SDL_GetPerformanceCounter();
    Uint64 m_Last = 0;
    float m_DeltaTime = 0;
   
    GameObject* m_Player = InitializeGameObject(100, 200, "images/preview.png");
    ms_RendererManager.AddGameObject(m_Player);
   
    while (m_IsRunning) {
        while (SDL_PollEvent(&m_Event)) {
            if (m_Event.type == SDL_QUIT) {
                m_IsRunning = false;
            }
        }

        SDL_SetRenderDrawColor(ms_RendererManager.GetRenderer(), 135, 206, 235, 255);
        SDL_RenderClear(ms_RendererManager.GetRenderer());
        

        m_Last = m_Now;
        m_Now = SDL_GetPerformanceCounter();
        m_DeltaTime = (float)((m_Now - m_Last) * 1000.0f / (float)SDL_GetPerformanceFrequency()) / 1000.0f;

        RigidBody m_RigidBody = m_Player->GetRigidBody();
        m_RigidBody.ApplyGravity(m_Player, m_DeltaTime, 9.8f, 400.0f);
        m_RigidBody.Update(m_DeltaTime);
        Blit(m_Player->GetTexture(), m_RigidBody.GetPosition().x, m_RigidBody.GetPosition().y, m_Player->GetWidth(), m_Player->GetHeight());

        SDL_RenderPresent(ms_RendererManager.GetRenderer());
    }
    delete m_Player;
    ms_RendererManager.Close();
    return 0;
}