#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "Components/MovementComponent.h"
#include <Game/EnemyCannonBall.h>

class Enemy : public GameObject {
public:
    std::vector<std::unique_ptr<EnemyCannonBall>> cannonBalls;
    using GameObject::GameObject;
    ~Enemy() = default;
    void UpdateComponents() override;
};
