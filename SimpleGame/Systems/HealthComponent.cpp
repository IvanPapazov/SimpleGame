#include "stdafx.h"
#include <Game/GameObject.h>
#include <Core/Component.h>
#include <Components/HealthComponent.h>
#include "Core/GameObjectManager.h"
#include <Components/RigidBodyComponent.h>
#include <Components/CollisionComponent.h>

void HealthComponent::Update()
{
	HealthComponent* health = GetOwner()->GetComponent<HealthComponent>();
	CollisionComponent * collision = GetOwner()->GetComponent<CollisionComponent>();
	if (collision->IsHitPast()) {
		health->m_Health--;
		collision->setHitPast(false);
	}
	if (health->m_Health <= 0 && health->m_IsActive) {
		health->m_IsActive = false;
	}
}