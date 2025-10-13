#include "stdafx.h"
#include "GameObject.h"
#include "MoveLeftRightComponent.h"
#include "RigidBodyComponent.h"

MoveLeftRightComponent::MoveLeftRightComponent(RigidBodyComponent* rb, float mass, float deltaTime)
	:m_RigidBodyComponent(rb), m_Mass(mass),m_deltaTime(deltaTime) {}

void MoveLeftRightComponent::Update()
{
	Vec2 velocity = m_RigidBodyComponent->GetVelocity();
	velocity.x = (1000000.0f) * GetDeltaTime();
	m_RigidBodyComponent->SetVelocity(velocity);
}
