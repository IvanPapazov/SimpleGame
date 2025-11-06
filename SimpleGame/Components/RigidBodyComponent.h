#pragma once
#include <Utils/Vec2.h>
#include "Core/Component.h"

class RigidBodyComponent : public Component
{
private:
    Vec2 m_Position;
    Vec2 m_Velocity;
    Vec2 m_Acceleration;

public:
    RigidBodyComponent() = default;

    RigidBodyComponent(const Vec2& pos);

    RigidBodyComponent(const RigidBodyComponent& other);

    ~RigidBodyComponent()=default;

    Vec2 getPosition() const { return m_Position; }
    Vec2 getVelocity() const { return m_Velocity; }
    Vec2 getAcceleration() const { return m_Acceleration; }

    void setPosition(const Vec2& position) { m_Position = position; }
    void setVelocity(const Vec2& velocity) { m_Velocity = velocity; }
    void setAcceleration(const Vec2& acceleration) { m_Acceleration = acceleration; }

    float DistanceTo(const Vec2& other) const;
};
