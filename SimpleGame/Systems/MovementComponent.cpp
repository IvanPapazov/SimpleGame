#include "stdafx.h"
#include <Game/GameObject.h>
#include <Core/Component.h>
#include "Core/GameObjectManager.h"
#include <Components/MovementComponent.h>
#include <Components/RigidBodyComponent.h>
#include <Components/CollisionComponent.h>
#include <Components/RenderComponent.h>
#include <Core/ResourceManager.h>
#include <Game/Game.h>
#include <SDL.h>

extern Game& game;
extern ResourceManager& g_ResourceManager;

void MovementComponent::Update()
{
    GameObject* owner = GetOwner();
    if (!owner) return;

    auto* rb = owner->GetComponent<RigidBodyComponent>();
    auto* col = owner->GetComponent<CollisionComponent>();
    auto* render = owner->GetComponent<RenderComponent>();
    if (!rb || !col || !render) return;

    const Uint8* keys = SDL_GetKeyboardState(nullptr);

    if (col->IsHit()) {
        g_ResourceManager.setCurrentState(render->GetTextureId(), "Hit");
        return;
    }

    ApplyGravity(rb, col);
    ApplyHorizontalMovement(rb, col, keys);
    ApplyJump(rb, col, keys);
    UpdateAnimation(col, render, keys);

    float dt = game.GetDeltaTime();
    rb->setVelocity(rb->getVelocity() + rb->getAcceleration() * dt);
    rb->setPosition(rb->getPosition() + rb->getVelocity() * dt);
    rb->setAcceleration(Vec2(0, 0));
}

void MovementComponent::ApplyGravity(RigidBodyComponent* rb, CollisionComponent* col)
{
    if (col->BottomCollision()) {
        Vec2 accel = rb->getAcceleration();
        accel.y = m_GravityScale;
        rb->setAcceleration(accel);
    }
    else {
        Vec2 vel = rb->getVelocity();
        vel.y = 0;
        rb->setVelocity(vel);
        rb->setPosition(rb->getPosition() - Vec2(0, 0.1f));
    }
}

void MovementComponent::ApplyHorizontalMovement(RigidBodyComponent* rb, CollisionComponent* col, const Uint8* keys)
{
    float x = 0.0f;
    float y = rb->getVelocity().y;
    rb->setVelocity(Vec2(0.0f, y));

    if (keys[SDL_SCANCODE_LEFT]) {
        if (col->LeftCollision()) {
            x -= m_Speed;
            col->SetRightCollision(true);
        }
    }
    if (keys[SDL_SCANCODE_RIGHT]) {
        if (col->RightCollision()) {
            x += m_Speed;
            col->SetLeftCollision(true);    
        }
    }

    if (keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_RIGHT]) {
        rb->setVelocity(Vec2(x, y));
    }
}

void MovementComponent::ApplyJump(RigidBodyComponent* rb, CollisionComponent* col, const Uint8* keys)
{
    if (keys[SDL_SCANCODE_UP] && !col->BottomCollision() && col->TopCollision()) {
        Vec2 vel = rb->getVelocity();
        vel.y = -m_Jump;
        rb->setVelocity(vel);
        col->SetBottomCollision(true);
    }

    if (!col->TopCollision()) {
        Vec2 vel = rb->getVelocity();
        if (vel.y < 0.0f) vel.y = 0.0f;
        rb->setVelocity(vel);
    }
}

void MovementComponent::UpdateAnimation(CollisionComponent* col, RenderComponent* render, const Uint8* keys)
{
    int texId = render->GetTextureId();

    if (keys[SDL_SCANCODE_UP] && !col->BottomCollision() && col->TopCollision()) {
        if (keys[SDL_SCANCODE_LEFT]) {
            g_ResourceManager.setCurrentState(texId, "JumpLeft");
        }
        else if (keys[SDL_SCANCODE_RIGHT]) {
            g_ResourceManager.setCurrentState(texId, "JumpRight");
        }
    }
    else if (col->BottomCollision()) {
        if (keys[SDL_SCANCODE_LEFT]) {
            g_ResourceManager.setCurrentState(texId, "FallLeft");
        }
        else if (keys[SDL_SCANCODE_RIGHT]) {
            g_ResourceManager.setCurrentState(texId, "FallRight");
        }
    }

    if (keys[SDL_SCANCODE_LEFT] && col->LeftCollision()) {
        g_ResourceManager.setCurrentState(texId, "RunLeft");
    }
    else if (keys[SDL_SCANCODE_RIGHT] && col->RightCollision()) {
        g_ResourceManager.setCurrentState(texId, "RunRight");
    }
    else {
        g_ResourceManager.setCurrentState(texId, "Idle");
    }
}
