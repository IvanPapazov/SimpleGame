#include <SDL.h>
#include <iostream>
#include "playerObject.h"
#include "physics.h"
#include "GameObject.h"


RigidBody::RigidBody(float x, float y)
    : m_Position(x, y), m_Velocity(0.0f, 0.0f), m_Acceleration(0.0f, 0.0f) {}

void RigidBody::Update(float deltaTime) {
    m_Velocity += m_Acceleration * deltaTime;
    m_Position += m_Velocity * deltaTime;
}

void RigidBody::ApplyGravity(GameObject* gameObject, float deltaTime, float gravity, float groundY) {
    RigidBody& rb = gameObject->GetRigidBody();

    Vec2 acc = rb.GetAcceleration();
    acc.y = gravity;
    rb.Update(deltaTime);

    Vec2 pos = rb.GetPosition();
    float height = gameObject->GetHeight();

    if (pos.y + height >= groundY) {
        pos.y = groundY - height;
        Vec2 vel = rb.GetVelocity();
        vel.y = 0.0f;
        acc.y = 0.0f;
        rb.SetVelocity(vel);
    }

    rb.SetPosition(pos);
    rb.SetAcceleration(acc);
}



