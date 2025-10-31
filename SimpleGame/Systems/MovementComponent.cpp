#include "stdafx.h"
#include <Game/GameObject.h>
#include <Core/Component.h>
#include "Core/GameObjectManager.h"
#include <Components/MovementComponent.h>
#include <Components/RigidBodyComponent.h>
#include <SDL.h>
#include <Core/ResourceManager.h>
#include <Components/RenderComponent.h>

extern ResourceManager& rm;

void MovementComponent::Update(GameObject* a)
{
	RigidBodyComponent* rbA = a->GetComponent<RigidBodyComponent>();
	CollisionComponent* result = a->GetComponent<CollisionComponent>();
	RenderComponent* render = a->GetComponent<RenderComponent>();
	float x;
	float y;

	//float NOW = SDL_GetPerformanceCounter();

	//m_DeltaTime = (float)((NOW - m_DeltaTimeLast) * 1000);
	//m_DeltaTimeLast = m_DeltaTime;
	rm.setCurrentState(render->GetTextureId(), "Idle");
	const Uint8* keys = SDL_GetKeyboardState(nullptr);\

	x = rbA->getAcceleration().x;
	if (result->IsBottom())
	{

		y = rbA->getAcceleration().y + m_GravityScale * 0.032;
		rbA->setAcceleration(Vec2(x, y));
		if (keys[SDL_SCANCODE_LEFT])
		{
			rm.setCurrentState(render->GetTextureId(), "FallLeft");
		}
		else if (keys[SDL_SCANCODE_RIGHT])
		{
			rm.setCurrentState(render->GetTextureId(), "FallRight");
		}
	}
	else
	{
		y = 0;
		rbA->setAcceleration(Vec2(x, y));

		Vec2 vel = rbA->getVelocity();
		vel.y = 0;
		rbA->setVelocity(vel);
	}

	//m_Left-m_Right-Jump
	x = rbA->getVelocity().x;
	y = rbA->getVelocity().y;
	rbA->setVelocity(Vec2(0, y));

	if (keys[SDL_SCANCODE_UP] && !result->IsBottom() && result->IsTop())
	{
		y = y - m_Jump;
		result->SetBottom(true);
		result->SetHit(false);
		rbA->setVelocity(Vec2(x, y));
		if (keys[SDL_SCANCODE_LEFT])
		{
			rm.setCurrentState(render->GetTextureId(), "JumpLeft");
		}
		else if (keys[SDL_SCANCODE_RIGHT])
		{
			rm.setCurrentState(render->GetTextureId(), "JumpRight");
		}
	}
	if (keys[SDL_SCANCODE_LEFT] && result->IsLeft())
	{
		x = rbA->getVelocity().x - m_Speed;
		result->SetRight(true);
		rbA->setVelocity(Vec2(x, y));
		rm.setCurrentState(render->GetTextureId(), "RunLeft");
	}
	if (keys[SDL_SCANCODE_RIGHT] && result->IsRight())
	{
		x = rbA->getVelocity().x + m_Speed;
		result->SetLeft(true);
		rbA->setVelocity(Vec2(x, y));
		rm.setCurrentState(render->GetTextureId(), "RunRight");
	}

	rbA->setVelocity(rbA->getVelocity() + rbA->getAcceleration() * 0.016f);
	rbA->setPosition(rbA->getPosition() + rbA->getVelocity() * 0.016f);
	rbA->setAcceleration(Vec2(0, 0));

}