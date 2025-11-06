#include "stdafx.h"
#include "Components/LevelTransitionComponent.h"
#include "Game/GameObject.h"
#include "Components/RigidBodyComponent.h"
#include "Components/CollisionComponent.h"
#include <Core/ResourceManager.h>
#include "Game/Game.h"
#include <Components/RenderComponent.h>
#include <iostream>


LevelTransitionComponent::LevelTransitionComponent(std::string level):
m_Level( level){}
extern ResourceManager& rm;
extern GameObjectManager& gameObjectManager;

void LevelTransitionComponent::Update() {
    GameObject* player = gameObjectManager.GetPlayer();
    CollisionComponent* doorCollider = GetOwner()->GetComponent<CollisionComponent>();
    RenderComponent* renderOwner = GetOwner()->GetComponent<RenderComponent>();
    CollisionComponent* col = player->GetComponent<CollisionComponent>();
    RenderComponent* render = player->GetComponent<RenderComponent>();

    rm.setCurrentState(renderOwner->GetTextureId(), "Idle");

    if (doorCollider->DoorCollision()) {

        rm.setCurrentState(renderOwner->GetTextureId(), "StayOpen");
        if (rm.getCurrentState(render->GetTextureId()) == "Idle" && !col->BottomCollision())
        {
            m_TransitionTimer.Update(3000, [&]() {
                Game::getInstance().RequestLevelChange(GetLevel());
                });
        }
       
    }
    
}
