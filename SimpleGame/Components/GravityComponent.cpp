#include "GameObject.h"
#include "GravityComponent.h"
#include "RigidBodyComponent.h"


GravityComponent::GravityComponent(RigidBodyComponent* rb,float mass)
	:m_RigidBodyComponent(rb), m_Mass(mass) {}

void GravityComponent::Update()
{
	Vec2 acc = m_RigidBodyComponent->GetAcceleration();
	acc.y = mg_Gravity * GetMass();

	Vec2 vel = m_RigidBodyComponent->GetVelocity();
	Vec2 velCalc = vel + (acc * 0.016f);
	m_RigidBodyComponent->SetVelocity(velCalc);

	Vec2 pos = m_RigidBodyComponent->GetPosition();
	Vec2 vel1 = m_RigidBodyComponent->GetVelocity();
	Vec2 posCalc = pos + vel1 * 0.016f;
	m_RigidBodyComponent->SetPosition(posCalc);

	Vec2 pos1 = m_RigidBodyComponent->GetPosition();
	//float height = gameObject->GetHeight();

	if (pos1.y + 80 >= 500)
	{
		pos1.y = 500.0f - 80.0f;
		Vec2 vel2 = m_RigidBodyComponent->GetVelocity();
		vel2.y = 0.0f;
		acc.y = 0.0f;
		m_RigidBodyComponent->SetVelocity(vel2);
	}

	m_RigidBodyComponent->SetPosition(pos1);
	m_RigidBodyComponent->SetAcceleration(acc);
}
 


