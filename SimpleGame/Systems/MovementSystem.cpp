#include "stdafx.h"
#include <Game/GameObject.h>
#include <Core/System.h>
#include "Core/GameObjectManager.h"
#include <Components/MovementComponent.h>
#include <Components/RigidBodyComponent.h>
#include <SDL.h>

void MovementComponent::Update(GameObject* a, std::unordered_map<int, GameObject*> gameObjects)
{
	RigidBodyComponent* rbA = a->GetComponent<RigidBodyComponent>();
	CollisionComponent* result = a->GetComponent<CollisionComponent>();
	float x;
	float y;

	//Left-Right-Jump
	const Uint8* keys = SDL_GetKeyboardState(nullptr);
	x = rbA->getVelocity().x;
	y = rbA->getVelocity().y;
	rbA->setVelocity(Vec2(0, y));
	if (keys[SDL_SCANCODE_LEFT] && result->IsLeft())
	{
		x = rbA->getVelocity().x - m_Speed;
		rbA->setVelocity(Vec2(x, y));
		result->SetRight(true);
	}
    if (keys[SDL_SCANCODE_RIGHT] && result->IsRight())
	{
		x = rbA->getVelocity().x + m_Speed;
		rbA->setVelocity(Vec2(x, y));
		result->SetLeft(true);
	}
    if ((keys[SDL_SCANCODE_UP] && !result->IsBottom()) || result->IsHit())
	{
		y = y -m_Jump;
		rbA->setVelocity(Vec2(x, y));
		result->SetBottom(true);
	}

	//Gravity
	x = rbA->getAcceleration().x;
	if (result->IsBottom()) {
		y = rbA->getAcceleration().y + m_GravityScale*1.5;
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