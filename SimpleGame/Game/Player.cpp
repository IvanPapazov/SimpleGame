#include "stdafx.h"
#include "Player.h"
#include "iostream"
#include <Components/RenderComponent.h>
#include <Components/HealthComponent.h>
#include <Utils/ReadInfo.h>


Player::Player(std::vector<Component*> comps)
	: GameObject(comps) 
{
	ReadInfo info;
	m_Live = info.ReadInfoHearts();
}

void Player::UpdateComponents()
{
	for (auto& [type, comp] : m_Components) {
		comp->Update();
	}
	HealthComponent* health = GetComponent<HealthComponent>();
	int hearts = health->GetHealth();

	UpdateHearts(hearts);
}

void Player::UpdateHearts(int hearts)
{
	for (auto& [id, heart] : m_Live) 
	{	
		if (hearts != 0)
		{
			RenderComponent* render = heart->GetComponent<RenderComponent>();
			render->Update();
			hearts--;
		}
	}
}
