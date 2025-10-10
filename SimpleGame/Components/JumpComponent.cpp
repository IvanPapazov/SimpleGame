#include "stdafx.h"
#include "GameObject.h"
#include "JumpComponent.h"
#include "RigidBodyComponent.h"

JumpComponent::JumpComponent(RigidBodyComponent* rb, float mass)
	:m_RigidBodyComponent(rb), m_Mass(mass) {}

void JumpComponent::Update()
{
	if (m_RigidBodyComponent->GetPosition().y + 80 >= 500)
	{
		Vec2 velocity = m_RigidBodyComponent->GetVelocity();
		velocity.y -= 250.0f;
		m_RigidBodyComponent->SetVelocity(velocity);
	}
}

