#include "stdafx.h"
#include <Game/GameObject.h>
#include <Core/Component.h>
#include <Components/HealthComponent.h>
#include <Core/GameObjectManager.h>
#include <Components/RigidBodyComponent.h>
#include <Components/CollisionComponent.h>
#include <Core/ResourceManager.h>
#include <Game/Game.h>

extern Game& game;
extern ResourceManager& g_ResourceManager;
extern GameObjectManager& gameObjectManager;

void HealthComponent::Update()
{
    GameObject* owner = GetOwner();
    if (!owner) return;

    auto* collision = owner->GetComponent<CollisionComponent>();
    auto* renderOwner = owner->GetComponent<RenderComponent>();
    if (!collision) return;
    
    if (collision->IsHitPast()) {
        m_Health--;
        collision->SetHitPast(false);
    }

    if (m_Health <= 0 && m_IsActive) {
        m_TransitionTimer.Update(3000, [&]() {
            game.RequestLevelChange("level_1");
            });
        g_ResourceManager.setCurrentState(renderOwner->GetTextureId(), "Dead");
    }
}
