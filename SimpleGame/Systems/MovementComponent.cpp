#include "stdafx.h"
#include <Game/GameObject.h>
#include <Core/Component.h>
#include "Core/GameObjectManager.h"
#include <Components/MovementComponent.h>
#include <Components/RigidBodyComponent.h>
#include <SDL.h>

void MovementComponent::Update(GameObject* a)
{
	RigidBodyComponent* rbA = a->GetComponent<RigidBodyComponent>();
	CollisionComponent* result = a->GetComponent<CollisionComponent>();
	float x;
	float y;

	//float NOW = SDL_GetPerformanceCounter();
	
	//m_DeltaTime = (float)((NOW - m_DeltaTimeLast) * 1000);
	//m_DeltaTimeLast = m_DeltaTime;

	x = rbA->getAcceleration().x;
	if (result->IsBottom())
	{

		y = rbA->getAcceleration().y + m_GravityScale * 0.032;
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

	//Left-Right-Jump
	const Uint8* keys = SDL_GetKeyboardState(nullptr);
	x = rbA->getVelocity().x;
	y = rbA->getVelocity().y;
	rbA->setVelocity(Vec2(0, y));


	if (keys[SDL_SCANCODE_UP] && !result->IsBottom())
	{
		y = y - m_Jump;
		result->SetBottom(true);
		rbA->setVelocity(Vec2(x, y));
	}
	if (keys[SDL_SCANCODE_LEFT] && result->IsLeft())
	{
		x = rbA->getVelocity().x - m_Speed;
		result->SetRight(true);
		rbA->setVelocity(Vec2(x, y));
	}
    if (keys[SDL_SCANCODE_RIGHT] && result->IsRight())
	{
		x = rbA->getVelocity().x + m_Speed;
		result->SetLeft(true);
		rbA->setVelocity(Vec2(x, y));
	}

	rbA->setVelocity(rbA->getVelocity() + rbA->getAcceleration() * 0.016f);
	rbA->setPosition(rbA->getPosition() + rbA->getVelocity() * 0.016f);
	rbA->setAcceleration(Vec2(0, 0));

}