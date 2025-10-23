#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "Components/MovementComponent.h"

class Player : public GameObject {
public:
    using GameObject::GameObject;
    ~Player() = default;
    void UpdateComponents(GameObject* obj) override;
};
