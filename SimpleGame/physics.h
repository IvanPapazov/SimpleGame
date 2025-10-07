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

class Rigidbody {
private:
    Vec2 position;
    Vec2 velocity;
    Vec2 acceleration;

public:
    Rigidbody(float x = 0.0f, float y = 0.0f);

    
    void update(float deltaTime);
    void applyGravity(GameObject& gameObject, float deltaTime, float gravity, float groundY);

    
    Vec2 getPosition();
    Vec2 getVelocity();
    Vec2 getAcceleration();

    
    void setPosition(Vec2& pos);
    void setVelocity(Vec2& vel);
    void setAcceleration(Vec2& acc);
};












