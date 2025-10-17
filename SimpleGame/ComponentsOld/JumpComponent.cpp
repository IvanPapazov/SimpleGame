#include "stdafx.h"
#include "JumpComponent.h"
#include "RigidBodyComponent.h"

JumpComponent::JumpComponent(RigidBodyComponent* rb, float height)
	:m_RigidBodyComponent(rb),m_Height(height) {}

void JumpComponent::Update()
{
	if (m_RigidBodyComponent->GetPosition().y + GetHeight() >= 500)
	{
		Vec2 velocity = m_RigidBodyComponent->GetVelocity();
		velocity.y -= 1.0f;
		m_RigidBodyComponent->SetVelocity(velocity);
	}
}

void JumpComponent::HandleAllEvents()
{
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_UP])
	{
		Update();
	}
}

