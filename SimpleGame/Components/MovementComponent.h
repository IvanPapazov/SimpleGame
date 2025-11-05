#pragma once
#include "stdafx.h"
#include <SDL.h>
#include <Core/Component.h>
#include <Game/GameObject.h>
#include <Components/RigidBodyComponent.h>
#include <Components/CollisionComponent.h>
#include <Components/RenderComponent.h>
#include <Utils/Vec2.h>
class MovementComponent : public Component
{
private:
	float m_GravityScale = 10.8f;
	float m_Speed = 3;
	float m_Jump = 7.5;

	void ApplyGravity(RigidBodyComponent* rb, CollisionComponent* col);
	void ApplyHorizontalMovement( RigidBodyComponent* rb, CollisionComponent* col, const Uint8* keys);
	void ApplyJump(RigidBodyComponent* rb, CollisionComponent* col, const Uint8* keys);
	void UpdateAnimation(CollisionComponent* col, RenderComponent* render, const Uint8* keys);

public:
	~MovementComponent()=default;
	MovementComponent(){};
	void Update();
};
