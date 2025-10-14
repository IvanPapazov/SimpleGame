#include "stdafx.h"
#include "GameObjectManager.h"
#include <Components/GravityComponent.h>
#include <Components/DrawComponent.h>

GameObjectManager::GameObjectManager() {};

void GameObjectManager::AddGameObject(GameObject* obj) {
	m_gameObjects[obj->GetId()] = obj;
}

GameObject* GameObjectManager::GetGameObject(int id) {
	auto it = m_gameObjects.find(id);
	return (it != m_gameObjects.end()) ? it->second : nullptr;
}

void GameObjectManager::RemoveGameObject(int id) {
	auto it = m_gameObjects.find(id);
	if (it != m_gameObjects.end()) {
		delete it->second;
		m_gameObjects.erase(it);
	}
}

void GameObjectManager::UpdateComponents()
{
	for (auto& [id, obj] : m_gameObjects) {
		obj->UpdateComponents();
	}
	if (m_GameObject!=nullptr)
	{
		m_GameObject->HandleAllEvents();
	}
}
void GameObjectManager::HandleAllEvents(float mouseX, float mouseY)
{
	SelectGameObjectAt(mouseX, mouseY, m_gameObjects);
}

const std::unordered_map<int, GameObject*>& GameObjectManager::GetAll() const {
	return m_gameObjects;
}

void GameObjectManager::SelectGameObjectAt(float mouseX, float mouseY, std::unordered_map<int, GameObject*> gameObjects)
{
	for (auto& element : gameObjects)
	{
		if (element.second->HasComponent<GravityComponent>())
		{
			SDL_Rect bounds;
			bounds.x = element.second->GetComponent<GravityComponent>()->GetRigidBodyComponent()->GetPosition().x;
			bounds.y = element.second->GetComponent<GravityComponent>()->GetRigidBodyComponent()->GetPosition().y;
			bounds.w = element.second->GetComponent<DrawComponent>()->GetWidth();
			bounds.h = element.second->GetComponent<DrawComponent>()->GetHeight();

			SDL_Point mousePoint = { mouseX, mouseY };
			if (SDL_PointInRect(&mousePoint, &bounds))
			{
				m_GameObject = element.second;
			}
		}
	}
}
