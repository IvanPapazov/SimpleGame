#pragma once
#include "stdafx.h"
#include <unordered_map>
#include <Game/GameObject.h>

class AIComponent : public System
{
private:
	float m_GravityScale = 9.8f;
	int m_Speed;
public:
	~AIComponent() = default;
	AIComponent(int health)
		:m_Speed(health) {}
	void Update(GameObject* object, std::unordered_map<int, GameObject*> gameObjects);
};
