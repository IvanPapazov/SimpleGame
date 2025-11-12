#include "stdafx.h"
#include "Player.h"
#include <iostream>
#include <Components/RenderComponent.h>
#include <Components/HealthComponent.h>
#include <Utils/ReadInfo.h>

Player::Player(std::vector<std::unique_ptr<Component>> comps)
    : GameObject(std::move(comps))
{
    ReadInfo info;
    m_Live = info.ReadInfoHearts();
}

void Player::UpdateComponents()
{
    for (auto& [type, comp] : m_Components) {
        if (comp) {
            comp->Update();
        }
    }

    HealthComponent* health = GetComponent<HealthComponent>();
    if (health) {
        int hearts = health->GetHealth();
        UpdateHearts(hearts);
    }
}

void Player::UpdateHearts(int hearts)
{
    for (auto& [id, heart] : m_Live)
    {
        if (hearts > 0 && heart) {
            RenderComponent* render = heart->GetComponent<RenderComponent>();
            if (render) {
                render->Update();
            }
            hearts--;
        }
    }
}
