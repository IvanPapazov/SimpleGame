#include "stdafx.h"
#include "Components/RampMovementComponent.h"
#include "Game/GameObject.h"
#include <Components/CollisionComponent.h>
#include <Components/RigidBodyComponent.h>

RampMovementComponent::RampMovementComponent(int speed)
    : AIComponent(speed){}

// Update method
void RampMovementComponent::Update(GameObject* object)
{
	RigidBodyComponent* rbA = object->GetComponent<RigidBodyComponent>();
	CollisionComponent* result = object->GetComponent<CollisionComponent>();
	float x = rbA->getPosition().x;
	float y = rbA->getPosition().y;
	
	if (result->IsBottom())
	{
		y = rbA->getPosition().y + GetSpeed()*0.016;		
	}
	if (result->IsTop())
	{
		y = rbA->getPosition().y - GetSpeed()*0.016;
	}
	rbA->setPosition(Vec2(x, y));
}
