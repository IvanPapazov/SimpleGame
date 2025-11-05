#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "Components/MovementComponent.h"

class Player : public GameObject {
protected:
    std::unordered_map<int, GameObject* > m_Live;

public:
    //using GameObject::GameObject;
    Player(std::vector<Component*> comps);
    ~Player() = default;
    void UpdateComponents() override;
    void UpdateHearts(int hearts);
};
