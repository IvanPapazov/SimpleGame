#include "stdafx.h"
#include "GameObject.h"
#include "MoveLeftComponent.h"
#include "RigidBodyComponent.h"

MoveLeftComponent::MoveLeftComponent(RigidBodyComponent* rb, float mass)
	:m_RigidBodyComponent(rb), m_Mass(mass) {}

void MoveLeftComponent::Update()
{
	Vec2 velocity = m_RigidBodyComponent->GetVelocity();
	velocity.x = 500.0f * -0.016;
	m_RigidBodyComponent->SetVelocity(velocity);
}
