#include "stdafx.h"
#include "FireBuletComponent.h"
#include "GameObject.h"
#include "MoveLeftRightComponent.h"
#include "RigidBodyComponent.h"
#include "ComponentManager.h"

FireBuletComponent::FireBuletComponent(RigidBodyComponent* rb_bulet, RigidBodyComponent* rb_enemy)
	:m_RigidBodyBulet(rb_bulet), m_RigidBodyEnemy(rb_enemy){}

void FireBuletComponent::Update()
{
	ComponentManager compManager;
	//compManager
	Vec2 velocity = m_RigidBodyBulet->GetVelocity();
	velocity.x = (1000000.0f) * GetDeltaTime();
	Vec2 position = m_RigidBodyEnemy->GetPosition();
	m_RigidBodyBulet->SetPosition(position);
	m_RigidBodyBulet->SetVelocity(velocity);
}
