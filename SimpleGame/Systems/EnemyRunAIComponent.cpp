#include "stdafx.h"
#include <unordered_map>
#include <Game/GameObject.h>
#include <Components/AIComponent.h>
#include <Components/CollisionComponent.h>
#include <Components/RigidBodyComponent.h>
#include <Components/EnemyRunAIComponent.h>
#include <Core/ResourceManager.h>
#include <Components/RenderComponent.h>
#include <Game/Game.h>

extern Game& game;
extern EventHandler& g_EventHandler;
extern ResourceManager& g_ResourceManager;

EnemyRunAIComponent::EnemyRunAIComponent(float speed)
    : AIComponent(speed) {}

void EnemyRunAIComponent::Update()
{
    auto* owner = GetOwner();
    if (!owner) return;

    auto* render = owner->GetComponent<RenderComponent>();
    auto* rb = owner->GetComponent<RigidBodyComponent>();
    auto* col = owner->GetComponent<CollisionComponent>();
    if (!render || !rb || !col) return;

    g_EventHandler.Notify(GravityEvent(owner), owner);

    // Reset horizontal velocity
    float x = 0.0f;
    float y = rb->getVelocity().y;

    // Movement logic
    if (col->LeftCollision()) {
        x = -GetSpeed();
        g_ResourceManager.setCurrentState(render->GetTextureId(), "RunLeft");
    }
    if (col->RightCollision()) {
        x = GetSpeed();
        g_ResourceManager.setCurrentState(render->GetTextureId(), "RunRight");
    }

    rb->setVelocity(Vec2(x, y));

    // Apply physics
    const float dt = game.GetDeltaTime();
    rb->setVelocity(rb->getVelocity() + rb->getAcceleration() * dt);
    rb->setPosition(rb->getPosition() + rb->getVelocity() * dt);
    rb->setAcceleration(Vec2(0, 0));
}
