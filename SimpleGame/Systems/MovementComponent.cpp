#include "stdafx.h"
#include <Game/GameObject.h>
#include <Core/Component.h>
#include "Core/GameObjectManager.h"
#include <Components/MovementComponent.h>
#include <Components/RigidBodyComponent.h>
#include <SDL.h>
#include <Core/ResourceManager.h>
#include <Components/RenderComponent.h>
#include <Game/Game.h>

extern Game& game;
extern ResourceManager& rm;

void MovementComponent::Update()
{
	RigidBodyComponent* rb = GetOwner()->GetComponent<RigidBodyComponent>();
	CollisionComponent* col = GetOwner()->GetComponent<CollisionComponent>();
	RenderComponent* render = GetOwner()->GetComponent<RenderComponent>();

	const Uint8* keys = SDL_GetKeyboardState(nullptr);

	if (col->IsHit()) {
		rm.setCurrentState(render->GetTextureId(), "Hit");
		return;
	}

	ApplyGravity(rb, col);
	ApplyHorizontalMovement(rb, col, keys);
	ApplyJump(rb, col, keys);
	
	UpdateAnimation(col, render, keys);


	rb->setVelocity(rb->getVelocity() + rb->getAcceleration() * game.GetDeltaTime());
	rb->setPosition(rb->getPosition() + rb->getVelocity() * game.GetDeltaTime());
	rb->setAcceleration(Vec2(0, 0));
}

void MovementComponent::ApplyGravity(RigidBodyComponent* rb, CollisionComponent* col)
{
	if (col->BottomCollision())
	{
		Vec2 accel = rb->getAcceleration();
		accel.y = m_GravityScale;
		rb->setAcceleration(accel);
	}
	else
	{
		
		Vec2 vel = rb->getVelocity();
		vel.y = 0;
		rb->setVelocity(vel);
		rb->setPosition(rb->getPosition() - Vec2(0, 0.1));
	}
}

void MovementComponent::ApplyHorizontalMovement(RigidBodyComponent* rb, CollisionComponent* col, const Uint8* keys)
{
	float x = 0;
	float y = rb->getVelocity().y;
	rb->setVelocity(Vec2(0, y));

	if (keys[SDL_SCANCODE_LEFT]) {
		if (!col->LeftCollision()) {
			rb->setVelocity(Vec2(0, y));
		}
		else {
			x -= m_Speed;
			col->SetRightCollision(true);
		}
	}
	if (keys[SDL_SCANCODE_RIGHT]) {
		if (!col->RightCollision()) {
			rb->setVelocity(Vec2(0, y));
		}
		else {
			x += m_Speed;
			col->SetLeftCollision(true);
		}
	}

	if (keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_RIGHT] ) {
		rb->setVelocity(Vec2(x, y));
	}

}

void MovementComponent::ApplyJump(RigidBodyComponent* rb, CollisionComponent* col, const Uint8* keys)
{
	if (keys[SDL_SCANCODE_UP] && !col->BottomCollision() && col->TopCollision())
	{
		Vec2 vel = rb->getVelocity();
		vel.y = -m_Jump; 
		rb->setVelocity(vel);
		col->SetBottomCollision(true); 
	}

	if (!col->TopCollision()) {
		Vec2 vel = rb->getVelocity();
		if (vel.y < 0) vel.y = 0;
		rb->setVelocity(vel);
	}
}

void MovementComponent::UpdateAnimation(CollisionComponent* col, RenderComponent* render, const Uint8* keys)
{
	int texId = render->GetTextureId();

	if (keys[SDL_SCANCODE_UP] && !col->BottomCollision() && col->TopCollision()) {
		if (keys[SDL_SCANCODE_LEFT]) {
			rm.setCurrentState(texId, "JumpLeft");
		}
		else if (keys[SDL_SCANCODE_RIGHT]) {
			rm.setCurrentState(texId, "JumpRight");
		}
	}
	else if (col->BottomCollision()) {
		if (keys[SDL_SCANCODE_LEFT]) {
			rm.setCurrentState(texId, "FallLeft");
		}
		else if (keys[SDL_SCANCODE_RIGHT]) {
			rm.setCurrentState(texId, "FallRight");
		}
	}

	if (keys[SDL_SCANCODE_LEFT] && col->LeftCollision()) {
		rm.setCurrentState(texId, "RunLeft");
	}
	else if (keys[SDL_SCANCODE_RIGHT] && col->RightCollision()) {
		rm.setCurrentState(texId, "RunRight");
	}
	else {
		rm.setCurrentState(texId, "Idle");
	}
}
