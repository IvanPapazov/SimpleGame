#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "Components/MovementComponent.h"

class EnemyCannonBall : public GameObject {
private:
    GameObject* owner;
public:
    using GameObject::GameObject;
    ~EnemyCannonBall() = default;
    void UpdateComponents() override;
};
