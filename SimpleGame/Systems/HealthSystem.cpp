#include "stdafx.h"
#include <Game/GameObject.h>
#include <Core/System.h>
#include <Components/HealthComponent.h>
#include "Core/GameObjectManager.h"
#include <Components/RigidBodyComponent.h>

void HealthComponent::Update(GameObject* object, std::unordered_map<int, GameObject*> gameObjects)
{
	HealthComponent* health = object->GetComponent<HealthComponent>();
	if (health->m_Health <= 0 && health->m_IsActive) {
		health->m_IsActive = false;
	}
}