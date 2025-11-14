#pragma once

#include <unordered_map>
#include <memory>
#include "../Game/GameObject.h"
#include <Events/EventSystem.h>


class GameObject; 
class EventSystem;
class GameObjectManager {
private:
    EventSystem* m_EventSystem;
public:
    static GameObjectManager& getInstance();

    GameObjectManager() = default;
    ~GameObjectManager() = default;
    GameObjectManager(const GameObjectManager& g) = delete;
    GameObjectManager(GameObjectManager&& g) = delete;

    void AddGameObject(std::unique_ptr<GameObject> obj);
    void UpdateAllGameObject();
    void RemoveGameObject(int id);
    void RemoveAllGameObject();

    GameObject* GetPlayer() const;
    GameObject* GetGameObject(int id) const;

    std::unordered_map<int, std::unique_ptr<GameObject>> m_gameObjects;
};
