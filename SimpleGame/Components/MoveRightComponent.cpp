#include "stdafx.h"
#include "GameObject.h"
#include "MoveRightComponent.h"
#include "RigidBodyComponent.h"

MoveRightComponent::MoveRightComponent(RigidBodyComponent* rb, float mass)
	:m_RigidBodyComponent(rb), m_Mass(mass) {}

void MoveRightComponent::Update()
{
	Vec2 velocity = m_RigidBodyComponent->GetVelocity();
	velocity.x = 500.0f * 0.016;
	m_RigidBodyComponent->SetVelocity(velocity);
}
