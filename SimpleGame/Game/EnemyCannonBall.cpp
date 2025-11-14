#include "stdafx.h"
#include "EnemyCannonBall.h"
#include "iostream"
#include <Components/HealthComponent.h>

void EnemyCannonBall::UpdateComponents()
{
    for (auto& [type, comp] : m_Components) {
        if (comp) {
            comp->Update();
        }
    }
}