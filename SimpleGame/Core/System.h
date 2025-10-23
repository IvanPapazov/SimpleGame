#pragma once

#include "stdafx.h"
#include <vector>
#include "../Game/GameObject.h"
#include "../Core/GameObjectManager.h"

class GameObject;
class System {
public:
    virtual ~System() = default;
    virtual void Update(GameObject* obj) {}
};