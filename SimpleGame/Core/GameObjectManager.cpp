#include "stdafx.h"
#include "GameObjectManager.h"
#include <Game/Player.h>


GameObjectManager& GameObjectManager::getInstance()
{
	static GameObjectManager ms_Instance;
	return ms_Instance;
}

void GameObjectManager::AddGameObject(GameObject* obj)
{
	if (obj) {
		m_gameObjects[obj->GetId()] = obj;
	}
}

void GameObjectManager::UpdateAllGameObject()
{
	for (auto& [key, object] : m_gameObjects)
	{
		object->UpdateComponents();
	}

}

void GameObjectManager::RemoveGameObject(int id)
{
	GameObject* obj = GetGameObject(id);
	m_gameObjects.erase(id);
	delete obj;
}

void GameObjectManager::RemoveAllGameObject()
{
	for (auto& [key, object] : m_gameObjects) {
		delete object;
	}
	m_gameObjects.clear();
}

GameObject* GameObjectManager::GetGameObject(int id) const 
{
	auto it = m_gameObjects.find(id);
	if (it != m_gameObjects.end()) 
	{
		return it->second;
	}
	return nullptr;
}

GameObject* GameObjectManager::GetPlayer() const {
	for (const auto& [id, obj] : m_gameObjects) {
		if (dynamic_cast<Player*>(obj)) {
			return obj;
		}
	}
	return nullptr;
}

