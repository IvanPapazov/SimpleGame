#include "stdafx.h"
#include "Components/RampMovementComponent.h"
#include "Game/GameObject.h"
#include <Components/CollisionComponent.h>
#include <Components/RigidBodyComponent.h>

RampMovementComponent::RampMovementComponent(int speed)
    : AIComponent(speed){}

void RampMovementComponent::Update()
{
	RigidBodyComponent* rbA = GetOwner()->GetComponent<RigidBodyComponent>();
	CollisionComponent* result = GetOwner()->GetComponent<CollisionComponent>();
	float x = rbA->getPosition().x;
	float y = rbA->getPosition().y;
	
	if (result->BottomCollision())
	{
		y = rbA->getPosition().y + GetSpeed()*0.016;		
	}
	if (result->TopCollision())
	{
		y = rbA->getPosition().y - GetSpeed()*0.016;
	}
	rbA->setPosition(Vec2(x, y));
}
