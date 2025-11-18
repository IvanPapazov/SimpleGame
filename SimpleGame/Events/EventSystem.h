#pragma once
#include <Events/EventHandler.h>


class GameObject;
class EventSystem {
public:
    void RegisterCollisionEvent(GameObject* object);
    void RegisterGravityEvents(GameObject* object);
    void RegisterCreateFireBallEvents(GameObject* object);
    void RegisterCreateLevelTransitionEvents(GameObject* object);
};

