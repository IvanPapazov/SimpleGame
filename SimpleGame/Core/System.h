#pragma once

#include "stdafx.h"
#include <vector>
#include "../Game/GameObject.h"
#include "../Core/GameObjectManager.h"

class GameObjectManager;
class System {
public:
    virtual ~System() = default;
    virtual void Update() {}

protected:
    GameObjectManager* gom;
};