#include "stdafx.h"
#include "Components/RigidBodyComponent.h"
#include "../Core/Component.h"

RigidBodyComponent::RigidBodyComponent(const Vec2& pos)
    : m_Position(pos), m_Velocity(0, 0), m_Acceleration(0, 0) {}

RigidBodyComponent::RigidBodyComponent(const RigidBodyComponent& other)
    : m_Position(other.m_Position),
    m_Velocity(other.m_Velocity),
    m_Acceleration(other.m_Acceleration) {}

float RigidBodyComponent::DistanceTo(const Vec2& other) const {
    float dx = m_Position.x - other.x;
    float dy = m_Position.y - other.y;
    return std::sqrt(dx * dx + dy * dy);
}

