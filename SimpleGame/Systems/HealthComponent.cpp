#include "stdafx.h"
#include <Game/GameObject.h>
#include <Core/System.h>
#include <Components/HealthComponent.h>
#include "Core/GameObjectManager.h"
#include <Components/RigidBodyComponent.h>
#include <Components/CollisionComponent.h>

void HealthComponent::Update(GameObject* object)
{
	HealthComponent* health = object->GetComponent<HealthComponent>();
	CollisionComponent * collision = object->GetComponent<CollisionComponent>();
	if (collision->IsHit())
	{
		//collision->SetHit(false);
		health->m_Health--;
	}
	if (health->m_Health <= 0 && health->m_IsActive) {
		health->m_IsActive = false;
	}
}