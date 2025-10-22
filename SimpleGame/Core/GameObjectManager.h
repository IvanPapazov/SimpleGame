#pragma once

#include <unordered_map>
#include "../Game/GameObject.h"  

class GameObject;
class GameObjectManager {
public:
	GameObjectManager();

	void AddGameObject(GameObject* obj);
	void UpdateAllGameObject();
	void RemoveGameObject(int id);

	GameObject* GetGameObject(int id) const;

	std::unordered_map<int, GameObject*> m_gameObjects;
};
