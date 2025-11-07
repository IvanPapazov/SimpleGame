#include "stdafx.h"
#include <unordered_map>
#include <Game/GameObject.h>
#include <Components/AIComponent.h>
#include <Components/CollisionComponent.h>
#include <Components/RigidBodyComponent.h>
#include <Components/EnemyRunAIComponent.h>
#include <Core/ResourceManager.h>
#include <Components/RenderComponent.h>
#include <Game/Game.h>

extern Game& game;
extern ResourceManager& rm;

EnemyRunAIComponent::EnemyRunAIComponent(float speed)
	:AIComponent(speed) {}

void EnemyRunAIComponent::Update()
{
	RenderComponent* render = GetOwner()->GetComponent<RenderComponent>();
	RigidBodyComponent* rbA = GetOwner()->GetComponent<RigidBodyComponent>();
	CollisionComponent* result = GetOwner()->GetComponent<CollisionComponent>();
	float x;
	float y;

	x = rbA->getAcceleration().x;
	if (result->BottomCollision())
	{
		Vec2 accel = rbA->getAcceleration();
		accel.y = m_GravityScale;
		rbA->setAcceleration(accel);
	}
	else
	{
		Vec2 vel = rbA->getVelocity();
		vel.y = 0;
		rbA->setVelocity(vel);
	}

	x = rbA->getVelocity().x;
	y = rbA->getVelocity().y;
	rbA->setVelocity(Vec2(0, y));

	if (result->LeftCollision())
	{
		x = rbA->getVelocity().x - GetSpeed();
		rm.setCurrentState(render->GetTextureId(), "RunLeft");
	}
	if (result->RightCollision())
	{
		x = rbA->getVelocity().x + GetSpeed();
		rm.setCurrentState(render->GetTextureId(), "RunRight");
	}
	rbA->setVelocity(Vec2(x, y));

	rbA->setVelocity(rbA->getVelocity() + rbA->getAcceleration() * game.GetDeltaTime());
	rbA->setPosition(rbA->getPosition() + rbA->getVelocity() * game.GetDeltaTime());
	rbA->setAcceleration(Vec2(0, 0));
}