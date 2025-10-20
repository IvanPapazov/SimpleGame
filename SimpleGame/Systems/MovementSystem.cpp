#include "stdafx.h"
#include <Game/GameObject.h>
#include <Core/System.h>
#include "Core/GameObjectManager.h"
#include <Components/MovementComponent.h>
#include <Components/RigidBodyComponent.h>

void MovementComponent::Update()
{
	//for (auto& [key, a] : gom.m_gameObjects) {
	//	RigidBodyComponent* rbA = a->GetComponent<RigidBodyComponent>();

	//	float x = rbA->getAcceleration().x;
	//	float y = rbA->getAcceleration().y + m_GravityScale;
	//	rbA->setAcceleration(Vec2(x, y));


	//	rbA->setVelocity(rbA->getVelocity() + rbA->getAcceleration() * 1.5);
	//	rbA->setPosition(rbA->getPosition() + rbA->getVelocity() * 1.5);
	//	rbA->setAcceleration(Vec2(0, 0));

	//	/*if (jump.shouldJump && jump.isGrounded) {
	//		rb.velocity.y = -jump.force;
	//		jump.shouldJump = false;
	//		jump.isGrounded = false;
	//	}*/
	//}
}