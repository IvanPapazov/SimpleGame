#include "stdafx.h"
#include "Components/RampMovementComponent.h"
#include "Game/GameObject.h"
#include <Components/CollisionComponent.h>
#include <Components/RigidBodyComponent.h>
#include <Game/Game.h>

RampMovementComponent::RampMovementComponent(float speed)
    : AIComponent(speed) {}

extern Game& game;

void RampMovementComponent::Update()
{
    GameObject* owner = GetOwner();
    if (!owner) return;

    auto* rb = owner->GetComponent<RigidBodyComponent>();
    auto* col = owner->GetComponent<CollisionComponent>();
    if (!rb || !col) return;

    float x = rb->getPosition().x;
    float y = rb->getPosition().y;

	if (col->BottomCollision())
	{
		y = rb->getPosition().y + GetSpeed() * game.GetDeltaTime();;
	}
	if (col->TopCollision())
	{
		y = rb->getPosition().y - GetSpeed() * game.GetDeltaTime();
	}
	rb->setPosition(Vec2(x, y));
}
