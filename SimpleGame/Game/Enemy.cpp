#include "stdafx.h"
#include "Enemy.h"
#include "iostream"
#include <Components/HealthComponent.h>

void Enemy::UpdateComponents()
{
    for (auto& [type, comp] : m_Components) {
        if (comp) {
            comp->Update();
        }
    }
}