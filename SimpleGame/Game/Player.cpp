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
	m_Live = info.ReadInfoItems();
}

void Player::UpdateComponents(GameObject* obj)
{
	for (auto& [type, comp] : m_Components) {
		comp->Update(obj);
	}
	HealthComponent* health = obj->GetComponent<HealthComponent>();
	UpdateHearts(health->GetHealth());
}

void Player::UpdateHearts(int hearts)
{
	for (auto& [type, comp] : m_Live) 
	{	
		if (hearts != 0)
		{
			RenderComponent* render = comp->GetComponent<RenderComponent>();
			render->Update(comp);
			hearts--;
		}
	}
}
