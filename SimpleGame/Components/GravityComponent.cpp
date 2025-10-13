#include "stdafx.h"
#include "GameObject.h"
#include "GravityComponent.h"
#include "RigidBodyComponent.h"


GravityComponent::GravityComponent(RigidBodyComponent* rb,float mass,float height)
	:m_RigidBodyComponent(rb), m_Mass(mass),m_Height(height) {}

void GravityComponent::Update()
{
	Vec2 acc = m_RigidBodyComponent->GetAcceleration();
	acc.y = mg_Gravity * GetMass();

	Vec2 vel = m_RigidBodyComponent->GetVelocity();
	Vec2 velCalc = vel + (acc * GetDeltaTime()*50);
	m_RigidBodyComponent->SetVelocity(velCalc);

	Vec2 pos = m_RigidBodyComponent->GetPosition();
	Vec2 vel1 = m_RigidBodyComponent->GetVelocity();
	Vec2 posCalc = pos + vel1 * GetDeltaTime();
	m_RigidBodyComponent->SetPosition(posCalc);

	Vec2 pos1 = m_RigidBodyComponent->GetPosition();

	if (pos1.y + GetHeight() >= 500)
	{
		pos1.y = 500.0f - GetHeight();
		Vec2 vel2 = m_RigidBodyComponent->GetVelocity();
		vel2.y = 0.0f;
		acc.y = 0.0f;
		m_RigidBodyComponent->SetVelocity(vel2);
	}

	m_RigidBodyComponent->SetPosition(pos1);
	m_RigidBodyComponent->SetAcceleration(acc);
}
 


