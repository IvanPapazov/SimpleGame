#pragma once
#include "stdafx.h"
#include <Game/GameObject.h>

class Door : public GameObject {
public:
    using GameObject::GameObject;
    ~Door() = default;
    void UpdateComponents() override;
};

