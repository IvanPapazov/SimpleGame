#pragma once

struct Vec2
{
    float x, y;
    Vec2(float x = 0, float y = 0) : x(x), y(y) {}
    Vec2 operator+(const Vec2& other) const
    {
        return Vec2(x + other.x, y + other.y);
    }
    Vec2 operator*(float scalar) const
    {
        return Vec2(x * scalar, y * scalar);
    }
    Vec2 operator/(float scalar) const
    {
        return Vec2(x / scalar, y / scalar);
    }
    Vec2& operator+=(const Vec2& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }
};

class RigidBodyComponent 
{
private:
    Vec2 m_Position;
    Vec2 m_Velocity;
    Vec2 m_Acceleration;

public: 
    RigidBodyComponent()
        :m_Position(0.0f, 0.0f), m_Velocity(0.0f, 0.0f), m_Acceleration(0.0f, 0.0f) {}

    RigidBodyComponent(const Vec2& pos, const Vec2& vel, const Vec2& acc)
        :m_Position(pos), m_Velocity(vel), m_Acceleration(acc) {}

    Vec2 GetPosition()
    {
        return m_Position;
    };
    Vec2 GetVelocity()
    {
        return m_Velocity;
    };
    Vec2 GetAcceleration()
    {
        return m_Acceleration;
    };


    void SetPosition(Vec2& pos)
    {
        m_Position = pos;
    };
    void SetVelocity(Vec2& vel)
    {
        m_Velocity = vel;
    };
    void SetAcceleration(Vec2& acc)
    {
        m_Acceleration = acc;
    };
};
