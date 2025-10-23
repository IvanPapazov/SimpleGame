#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "Components/MovementComponent.h"

class Terrain : public GameObject {
public:
    using GameObject::GameObject;
    void UpdateComponents(GameObject* obj) override;
};
