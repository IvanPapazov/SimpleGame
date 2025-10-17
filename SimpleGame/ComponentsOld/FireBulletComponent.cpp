#include "stdafx.h"
#include "FireBulletComponent.h"
#include "MoveLeftRightComponent.h"
#include "RigidBodyComponent.h"
#include "DrawComponent.h"

FireBulletComponent::FireBulletComponent(RigidBodyComponent* rb)
:m_RigidBodyComponent(rb){}

void FireBulletComponent::Update()
{
	Uint64 m_Now = SDL_GetPerformanceCounter();
	m_deltaTime = (float)(m_Now - m_Last) / (float)SDL_GetPerformanceFrequency();
	m_Last = m_Now;
	Vec2 velocity = GetRigidBodyComponent()->GetVelocity();
	velocity.x = (100.0f) * m_deltaTime;
	Vec2 position =GetRigidBodyComponent()->GetPosition();
	position += velocity;
	GetRigidBodyComponent()->SetVelocity(velocity);
	GetRigidBodyComponent()->SetPosition(position);
}
