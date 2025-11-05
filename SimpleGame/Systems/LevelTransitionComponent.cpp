#include "stdafx.h"
#include "Components/LevelTransitionComponent.h"
#include "Game/GameObject.h"
#include "Components/RigidBodyComponent.h"
#include "Components/CollisionComponent.h"
#include <Core/ResourceManager.h>
#include "Game/Game.h"
#include <Components/RenderComponent.h>


LevelTransitionComponent::LevelTransitionComponent(){}
extern ResourceManager& rm;
extern GameObjectManager& gameObjectManager;

void LevelTransitionComponent::Update() {
    CollisionComponent* doorCollider = GetOwner()->GetComponent<CollisionComponent>();

    GameObject* player = gameObjectManager.GetPlayer();
    CollisionComponent* col = player->GetComponent<CollisionComponent>();
    RenderComponent* render = player->GetComponent<RenderComponent>();
    RenderComponent* renderOwner = GetOwner()->GetComponent<RenderComponent>();
    

    if (doorCollider->DoorCollision()) {
        rm.setCurrentState(renderOwner->GetTextureId(), "Open");

        if (rm.getCurrentState(render->GetTextureId()) == "Idle" && !col->BottomCollision()) {
            if (!m_TimerStarted) {
                m_TransitionTimer.Start();
                m_TimerStarted = true;
            }

            if (m_TransitionTimer.GetElapsed() > 5000) {
                rm.setCurrentState(renderOwner->GetTextureId(), "StayOpen");
                Game::getInstance().RequestLevelChange("level_2");
                m_TransitionTimer.Stop();
                m_TimerStarted = false;
            }
        }
    }
    else 
    {
        m_TransitionTimer.Stop();
        m_TimerStarted = false;
        rm.setCurrentState(renderOwner->GetTextureId(), "Close");
        return;
    }
    
}
