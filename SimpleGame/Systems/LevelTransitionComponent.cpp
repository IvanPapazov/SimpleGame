#include "stdafx.h"
#include "Components/LevelTransitionComponent.h"
#include "Game/GameObject.h"
#include "Components/RigidBodyComponent.h"
#include "Components/CollisionComponent.h"
#include <Core/ResourceManager.h>
#include "Game/Game.h"
#include <Components/RenderComponent.h>
#include <iostream>

LevelTransitionComponent::LevelTransitionComponent(std::string level)
    : m_NextLevel(std::move(level)) {}

extern Game& game;
extern ResourceManager& g_ResourceManager;
extern GameObjectManager& gameObjectManager;

void LevelTransitionComponent::Update() {
    GameObject* player = gameObjectManager.GetPlayer();
    GameObject* owner = GetOwner();
    if (!player || !owner) return;

    auto* doorCollider = owner->GetComponent<CollisionComponent>();
    auto* renderOwner = owner->GetComponent<RenderComponent>();
    auto* playerCollider = player->GetComponent<CollisionComponent>();
    auto* playerRender = player->GetComponent<RenderComponent>();

    if (!doorCollider || !renderOwner || !playerCollider || !playerRender) return;

    g_ResourceManager.setCurrentState(renderOwner->GetTextureId(), "Idle");

    if (doorCollider->DoorCollision()) {
        g_ResourceManager.setCurrentState(renderOwner->GetTextureId(), "StayOpen");

        if (g_ResourceManager.getCurrentState(playerRender->GetTextureId()) == "Idle") {
            m_TransitionTimer.Update(1500, [&]() {
                game.RequestLevelChange(getNextLevel());
                });
        }
        else {
            m_TransitionTimer.Stop();
        }
    }
}
