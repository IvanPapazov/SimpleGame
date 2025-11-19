#pragma once
#include <typeindex>
#include <Game/GameObject.h>

class GameObject;

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

class BallEvent : public Event {
public:
    GameObject* object;
    BallEvent(GameObject* obj)
        : object(obj) {}
};

class LevelTransitionPlayerPositionEvent : public Event {
public:
    GameObject* object;
    LevelTransitionPlayerPositionEvent(GameObject* obj)
        : object(obj) {}
};

class SpotlightEvent : public Event {
public:
    GameObject* object;
    SpotlightEvent(GameObject* obj)
        : object(obj) {}
};