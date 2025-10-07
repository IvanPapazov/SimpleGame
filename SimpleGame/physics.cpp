#include <SDL.h>
#include <iostream>
#include "playerObject.h"
#include "physics.h"
#include "GameObject.h"


Rigidbody::Rigidbody(float x, float y)
    : position(x, y), velocity(0.0f, 0.0f), acceleration(0.0f, 0.0f) {}

void Rigidbody::update(float deltaTime) {
    velocity += acceleration * deltaTime;
    position += velocity * deltaTime;
}

void Rigidbody::applyGravity(GameObject* gameObject, float deltaTime, float gravity, float groundY) {
    Rigidbody& rb = gameObject->getRigidbody();

    Vec2 acc = rb.getAcceleration();
    acc.y = gravity;
    rb.update(deltaTime);

    Vec2 pos = rb.getPosition();
    float height = gameObject->getHeight();

    if (pos.y + height >= groundY) {
        pos.y = groundY - height;
        Vec2 vel = rb.getVelocity();
        vel.y = 0.0f;
        acc.y = 0.0f;
        rb.setVelocity(vel);
    }

    rb.setPosition(pos);
    rb.setAcceleration(acc);
}



