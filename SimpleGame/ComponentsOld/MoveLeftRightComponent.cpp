#include "stdafx.h"
#include "MoveLeftRightComponent.h"
#include "RigidBodyComponent.h"

MoveLeftRightComponent::MoveLeftRightComponent(RigidBodyComponent* rb, float mass)
	:m_RigidBodyComponent(rb), m_Mass(mass) {}

void MoveLeftRightComponent::Update()
{
	Vec2 velocity = m_RigidBodyComponent->GetVelocity();
	velocity.x = (1000000.0f) * m_deltaTime;
	m_RigidBodyComponent->SetVelocity(velocity);
}

void MoveLeftRightComponent::HandleAllEvents()
{
	Uint64 m_Now = SDL_GetPerformanceCounter();
	m_deltaTime = (float)(m_Now - m_Last) / (float)SDL_GetPerformanceFrequency();
	m_Last = m_Now;
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_LEFT])
	{
		m_deltaTime = -m_deltaTime;		
	}
	else if (state[SDL_SCANCODE_RIGHT])
	{
		m_deltaTime;		
	}
	else
	{
		m_deltaTime = 0.0f;		
	}
	Update();
}
