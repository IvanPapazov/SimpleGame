#pragma once
#include <Utils/Vec2.h>

class RigidBodyComponent
{
private:
    Vec2 m_Position;
    Vec2 m_Velocity;
    Vec2 m_Acceleration;
public:
    RigidBodyComponent() = default;

    RigidBodyComponent(const Vec2& pos)
        : m_Position(pos), m_Velocity(0, 0), m_Acceleration(0, 0) {}

    RigidBodyComponent(const RigidBodyComponent& other)
        : m_Position(other.m_Position),
        m_Velocity(other.m_Velocity),
        m_Acceleration(other.m_Acceleration) {}
};
