#include "stdafx.h"
#include "Player.h"
#include "iostream"

void Player::UpdateComponents(GameObject* obj)
{
	for (auto& [type, comp] : m_Components) {
		comp->Update(obj);
	}
}