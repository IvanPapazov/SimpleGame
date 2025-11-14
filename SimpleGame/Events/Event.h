#pragma once
#include <typeindex>
#include <Game/GameObject.h>

class Event {
public:
    virtual ~Event() = default;
};

class CollisionEvent : public Event {
public:
    GameObject* objectA;
    GameObject* objectB;

    CollisionEvent(GameObject* a, GameObject* b)
        : objectA(a), objectB(b) {}
};

class GravityEvent : public Event {
public:
    GameObject* object;
    GravityEvent(GameObject* obj) 
        : object(obj) {}
};