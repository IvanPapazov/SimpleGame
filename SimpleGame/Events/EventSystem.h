#pragma once
#include <Events/EventHandler.h>

class EventSystem {
public:
    void RegisterCollisionEvents(GameObject* object);
    void RegisterGravityEvents(GameObject* object);
};

