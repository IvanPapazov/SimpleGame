#pragma once
#include "stdafx.h"
#include "GameObject.h"

class Heart : public GameObject {
public:
    using GameObject::GameObject;
    void UpdateComponents() override;
};


