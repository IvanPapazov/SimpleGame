#include <SDL.h>
#include <iostream>
#include "window.h"
#include "playerObject.h"

const float GRAVITY = 9.8f;
const float GROUND_Y= NULL;

struct Vec2 {
    float x, y;
    Vec2(float x = 0, float y = 0) : x(x), y(y) {}
    Vec2 operator+(const Vec2& other) const { return Vec2(x + other.x, y + other.y); }
    Vec2 operator*(float scalar) const { return Vec2(x * scalar, y * scalar); }
    Vec2& operator+=(const Vec2& other) { x += other.x; y += other.y; return *this; }
};

struct Rigidbody {
    Vec2 position;
    Vec2 velocity;
    Vec2 acceleration;

    Rigidbody(float x, float y) {
        position = Vec2(x, y);
        velocity = Vec2(0, 0);
        acceleration = Vec2(0, GRAVITY);
    }

    void update(float dt) {
        velocity += acceleration * dt;
        position += velocity * dt;     
    }
};

void gravity(Entity object)
{
    //vy += GRAVITY;
    //object.y += vy;

    // Simple ground collision
    //if (object.y + object.h >= GROUND_Y) {
    //    object.y = GROUND_Y - object.h;
    //   // vy = 0;
    //}

    blit(player.texture, player.x, player.y, player.w, player.h);
}
























































