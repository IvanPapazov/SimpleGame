#include "GameObject.h"
#include "MoveComponent.h"
#include "RigidBodyComponent.h"

MoveComponent::MoveComponent(RigidBodyComponent* rb, float mass)
	:m_RigidBodyComponent(rb), m_Mass(mass) {}

void MoveComponent::Update()
{
	Vec2 velocity = m_RigidBodyComponent->GetVelocity();
	velocity.x = 150.0f * 1000.0f * 0.016;
	m_RigidBodyComponent->SetVelocity(velocity);
}
