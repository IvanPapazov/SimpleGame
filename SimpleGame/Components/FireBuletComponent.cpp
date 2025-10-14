#include "stdafx.h"
#include "FireBuletComponent.h"
#include "GameObject.h"
#include "MoveLeftRightComponent.h"
#include "RigidBodyComponent.h"
#include "DrawComponent.h"
#include "GameObjectFactory.h"

FireBuletComponent::FireBuletComponent(){}

void FireBuletComponent::Update()
{
	Vec2 velocity = m_bulet->GetComponent<DrawComponent>()->GetRigidBodyComponent()->GetVelocity();
	velocity.x = (100000.0f) * GetDeltaTime();
	Vec2 position = m_bulet->GetComponent<DrawComponent>()->GetRigidBodyComponent()->GetPosition();
	position += velocity;
	m_bulet->GetComponent<DrawComponent>()->GetRigidBodyComponent()->SetVelocity(velocity);
	m_bulet->GetComponent<DrawComponent>()->GetRigidBodyComponent()->SetPosition(position);
}
