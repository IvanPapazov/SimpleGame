#pragma once
#include "stdafx.h"
#include <Game/GameObject.h>

class Pathways : public GameObject {
public:
    using GameObject::GameObject;
    ~Pathways() = default;
    void UpdateComponents() override;
};

