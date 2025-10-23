#include "stdafx.h"
#include <unordered_map>
#include <Game/GameObject.h>
#include <Components/AIComponent.h>
#include <Components/CollisionComponent.h>
#include <Components/RigidBodyComponent.h>

void AIComponent::Update(GameObject* object)
{
	RigidBodyComponent* rbA = object->GetComponent<RigidBodyComponent>();
	CollisionComponent* result = object->GetComponent<CollisionComponent>();
	float x;
	float y;
	x = rbA->getVelocity().x;
	y = rbA->getVelocity().y;
	rbA->setVelocity(Vec2(0, y));
	if (result->IsLeft() && !result->IsRight())
	{
		x = rbA->getVelocity().x - m_Speed;
		rbA->setVelocity(Vec2(x, y));
	}
	if (result->IsRight())
	{
		x = rbA->getVelocity().x + m_Speed;
		rbA->setVelocity(Vec2(x, y));
	}

	x = rbA->getAcceleration().x;
	if (result->IsBottom()) {
		y = rbA->getAcceleration().y + m_GravityScale * 1.5;
		rbA->setAcceleration(Vec2(x, y));
	}
	else
	{
		y = 0;
		rbA->setAcceleration(Vec2(x, y));

		Vec2 vel = rbA->getVelocity();
		vel.y = 0;
		rbA->setVelocity(vel);
	}
	rbA->setVelocity(rbA->getVelocity() + rbA->getAcceleration() * 0.016f);
	rbA->setPosition(rbA->getPosition() + rbA->getVelocity() * 0.016f);
	rbA->setAcceleration(Vec2(0, 0));
}