#include "stdafx.h"
#include "Enemy.h"
#include "iostream"
#include <Components/HealthComponent.h>

void Enemy::UpdateComponents(GameObject* obj)
{
	for (auto& [type, comp] : m_Components) {
		comp->Update(obj);
		/*HealthComponent* health = obj->GetComponent<HealthComponent>();
		if (!health->IsActive())
		{
			GameObjectManager gom;
			gom.RemoveGameObject(obj->GetId());
			return;
		}*/
	}
}