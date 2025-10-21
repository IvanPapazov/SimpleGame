#pragma once
#include "stdafx.h"
#include <Components/CollisionComponent.h>
class MovementComponent : public System
{
private:
	float m_GravityScale = 9.8f;
	float m_Speed = 10;
	float m_Jump = 50;
public:
	MovementComponent(){};
	void Update(GameObject* object, std::unordered_map<int, GameObject*> gameObjects);
};
