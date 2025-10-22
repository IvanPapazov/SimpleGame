#include "stdafx.h"
#include "Enemy.h"
#include "iostream"
#include <Components/HealthComponent.h>

void Enemy::UpdateComponents(GameObject* obj, std::unordered_map<int, GameObject*> gameObjects)
{
	for (auto& [type, comp] : m_Components) {
		comp->Update(obj, gameObjects);
		/*HealthComponent* health = obj->GetComponent<HealthComponent>();
		if (!health->IsActive())
		{
			GameObjectManager gom;
			gom.RemoveGameObject(obj->GetId());
			return;
		}*/
	}
}