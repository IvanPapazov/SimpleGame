#include "stdafx.h"
#include "GameObject.h"
#include "GravityComponent.h"
#include "RigidBodyComponent.h"

constexpr float GROUND_Y = 500.0f;

GravityComponent::GravityComponent(RigidBodyComponent* rb,float mass,float height)
	:m_RigidBodyComponent(rb), m_Mass(mass),m_Height(height) {}

void GravityComponent::HandleAllEvents() {
}

void GravityComponent::Update()
{
    Uint64 m_Now = SDL_GetPerformanceCounter();
    m_deltaTime = (float)(m_Now - m_Last) / (float)SDL_GetPerformanceFrequency();
    m_Last = m_Now;

    Vec2 acceleration = m_RigidBodyComponent->GetAcceleration();
    acceleration.y = mg_Gravity * m_Mass;

    Vec2 velocity = m_RigidBodyComponent->GetVelocity();
    velocity += acceleration * m_deltaTime * 50.0f;

    Vec2 position = m_RigidBodyComponent->GetPosition();
    position += velocity * m_deltaTime;

    if (position.y + m_Height >= GROUND_Y)
    {
        position.y = GROUND_Y - m_Height;
        velocity.y = 0.0f;
        acceleration.y = 0.0f;
    }

    m_RigidBodyComponent->SetAcceleration(acceleration);
    m_RigidBodyComponent->SetVelocity(velocity);
    m_RigidBodyComponent->SetPosition(position);
}
 


