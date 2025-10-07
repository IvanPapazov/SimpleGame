#include <SDL.h>
#include <iostream>
#include "playerObject.h"
#include "physics.h"
#include "GameObject.h"

#define Gravity 500.0f
#define JumpForce 300.0f
#define Ground 500.0f

RigidBody::RigidBody(float x, float y)
    : m_Position(x, y), m_Velocity(0.0f, 0.0f), m_Acceleration(0.0f, 0.0f) {}

void RigidBody::Update(float deltaTime) {
    m_Velocity += m_Acceleration * deltaTime;
    m_Position += m_Velocity * deltaTime;
}

void RigidBody::ApplyGravityForce(GameObject* gameObject, float deltaTime) {
    RigidBody& rb = gameObject->GetRigidBody();

    Vec2 acc = rb.GetAcceleration();
    acc.y = Gravity;
    rb.Update(deltaTime);

    Vec2 pos = rb.GetPosition();
    float height = gameObject->GetHeight();

    if (pos.y + height >= Ground) {
        pos.y = Ground - height;
        Vec2 vel = rb.GetVelocity();
        vel.y = 0.0f;
        acc.y = 0.0f;
        rb.SetVelocity(vel);
    }

    rb.SetPosition(pos);
    rb.SetAcceleration(acc);
}

void RigidBody::ApplyJumpForce(GameObject* gameObject, float deltaTime) {
    RigidBody& rb = gameObject->GetRigidBody();
    rb.m_Velocity.y = -JumpForce;
  
}



