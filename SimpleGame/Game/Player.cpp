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
			render->Update(heart);
			hearts--;
		}
	}
}
