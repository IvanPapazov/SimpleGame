#pragma once

#include <unordered_map>
#include "../Game/GameObject.h"  

class GameObject;
class GameObjectManager {
public:
    GameObjectManager();  

    void AddGameObject(GameObject* obj);

    std::unordered_map<int, GameObject*> m_gameObjects;
};
