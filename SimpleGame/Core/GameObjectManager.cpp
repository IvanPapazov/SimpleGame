#include "stdafx.h"
#include "GameObjectManager.h"


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
		object->UpdateComponents(object);
	}

}

void GameObjectManager::RemoveGameObject(int id)
{
	GameObject* obj = GetGameObject(id);
	m_gameObjects.erase(obj->GetId());
	delete obj;
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
