#pragma once
#include "stdafx.h"
#include "GameObject.h"

class Player : public GameObject {
protected:
    std::unordered_map<int, std::unique_ptr<GameObject>> m_Live;

public:
    Player(std::vector<std::unique_ptr<Component>> comps);
    ~Player() override = default;

    void UpdateComponents() override;
    void UpdateHearts(int hearts);
};
