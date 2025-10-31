#pragma once

#include "stdafx.h"
#include <vector>
#include "../Game/GameObject.h"
#include "../Core/GameObjectManager.h"

class GameObject;
class Component {
public:
    virtual ~Component() = default;
    virtual void Update(GameObject* obj) {}

};