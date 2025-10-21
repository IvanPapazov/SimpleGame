#pragma once
#include "stdafx.h"
class HealthComponent : public System
{
private:
	bool m_IsActive = true;
	int m_Health;
public:
	HealthComponent(int health)
		:m_Health(health){}

	void Update(GameObject* object, std::unordered_map<int, GameObject*> gameObjects);
};
