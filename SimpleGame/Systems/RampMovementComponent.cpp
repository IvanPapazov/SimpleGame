#include "stdafx.h"
#include "Components/RampMovementComponent.h"
#include "Game/GameObject.h"
#include <Components/CollisionComponent.h>
#include <Components/RigidBodyComponent.h>
#include <Game/Game.h>

RampMovementComponent::RampMovementComponent(float speed)
    : AIComponent(speed){}

extern Game& game;
void RampMovementComponent::Update()
{
	RigidBodyComponent* rbA = GetOwner()->GetComponent<RigidBodyComponent>();
	CollisionComponent* result = GetOwner()->GetComponent<CollisionComponent>();
	float x = rbA->getPosition().x;
	float y = rbA->getPosition().y;
	
	if (result->BottomCollision())
	{
		y = rbA->getPosition().y + GetSpeed() * game.GetDeltaTime();;
	}
	if (result->TopCollision())
	{
		y = rbA->getPosition().y - GetSpeed()* game.GetDeltaTime();
	}
	rbA->setPosition(Vec2(x, y));
}
