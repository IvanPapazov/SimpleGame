#pragma once

#include <unordered_map>
#include "../Game/GameObject.h"  

class GameObject;
class GameObjectManager {
public:
	GameObjectManager() = default;
	~GameObjectManager() = default;
	GameObjectManager(const GameObjectManager& g) = delete;
	GameObjectManager(GameObjectManager&& g) = delete;

	void AddGameObject(GameObject* obj);
	void UpdateAllGameObject();
	void RemoveGameObject(int id);
	static GameObjectManager& getInstance();

	GameObject* GetGameObject(int id) const;

	std::unordered_map<int, GameObject*> m_gameObjects;

};
