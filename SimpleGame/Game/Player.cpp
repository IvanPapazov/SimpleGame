#include "stdafx.h"
#include "Player.h"
#include "iostream"

void Player::UpdateComponents(GameObject* obj, std::unordered_map<int, GameObject*> gameObjects)
{
	for (auto& [type, comp] : m_Components) {
		comp->Update(obj,gameObjects);
	}
}