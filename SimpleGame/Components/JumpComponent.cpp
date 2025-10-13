#include "stdafx.h"
#include "GameObject.h"
#include "JumpComponent.h"
#include "RigidBodyComponent.h"

JumpComponent::JumpComponent(RigidBodyComponent* rb, float height)
	:m_RigidBodyComponent(rb),m_Height(height) {}

void JumpComponent::Update()
{
	if (m_RigidBodyComponent->GetPosition().y + GetHeight() >= 500)
	{
		Vec2 velocity = m_RigidBodyComponent->GetVelocity();
		velocity.y -= 1000.0f;
		m_RigidBodyComponent->SetVelocity(velocity);
	}
}

