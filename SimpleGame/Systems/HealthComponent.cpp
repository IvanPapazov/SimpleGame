#include "stdafx.h"
#include <Game/GameObject.h>
#include <Core/Component.h>
#include <Components/HealthComponent.h>
#include <Core/GameObjectManager.h>
#include <Components/RigidBodyComponent.h>
#include <Components/CollisionComponent.h>

void HealthComponent::Update()
{
    GameObject* owner = GetOwner();
    if (!owner) return;

    auto* collision = owner->GetComponent<CollisionComponent>();
    if (!collision) return;

    if (collision->IsHitPast()) {
        m_Health--;
        collision->SetHitPast(false);
    }

    if (m_Health <= 0 && m_IsActive) {
        m_IsActive = false;
    }
}
