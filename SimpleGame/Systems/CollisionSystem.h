#pragma once
#include "Core/System.h"

class CollisionSystem : public System
{
private:
public:
	void Update(float deltaTime, ComponentManager* cm);
	bool CheckCollision(CollisionComponent* a, CollisionComponent* b);
};

