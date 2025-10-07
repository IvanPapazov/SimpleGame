#pragma once
#include <SDL.h>
#include <iostream>
#include "playerObject.h"

class GameObject;

struct Vec2 {
    float x, y;
    Vec2(float x = 0, float y = 0) : x(x), y(y) {}
    Vec2 operator+(const Vec2& other) const { return Vec2(x + other.x, y + other.y); }
    Vec2 operator*(float scalar) const { return Vec2(x * scalar, y * scalar); }
    Vec2& operator+=(const Vec2& other) { x += other.x; y += other.y; return *this; }
};

class RigidBody {
private:
    Vec2 m_Position;
    Vec2 m_Velocity;
    Vec2 m_Acceleration;

public:
    RigidBody(float x = 0.0f, float y = 0.0f);

    
    void Update(float deltaTime);
    void ApplyGravityForce(GameObject* gameObject, float deltaTime);
    void ApplyJumpForce(GameObject* gameObject, float deltaTime);

    
    Vec2 GetPosition() { return m_Position; };
    Vec2 GetVelocity() { return m_Velocity; };
    Vec2 GetAcceleration() { return m_Acceleration; };

    
    void SetPosition(Vec2& pos) { m_Position = pos; };
    void SetVelocity(Vec2& vel) { m_Velocity = vel; };
    void SetAcceleration(Vec2& acc) { m_Acceleration = acc; };
};












