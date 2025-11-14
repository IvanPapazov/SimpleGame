#include "stdafx.h"
#include "Components/RigidBodyComponent.h"
#include "../Core/Component.h"

RigidBodyComponent::RigidBodyComponent(const Vec2& pos, float gravity)
    : m_GravityScale(gravity), m_Position(pos), m_Velocity(0, 0), m_Acceleration(0, 0) {}

RigidBodyComponent::RigidBodyComponent(const RigidBodyComponent& other)
    : m_Position(other.m_Position),
    m_Velocity(other.m_Velocity),
    m_Acceleration(other.m_Acceleration) {}


