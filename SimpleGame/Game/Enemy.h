#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "Components/MovementComponent.h"

class Enemy : public GameObject {
public:
    using GameObject::GameObject;
    ~Enemy() = default;
    void UpdateComponents(GameObject* obj) override;
};
