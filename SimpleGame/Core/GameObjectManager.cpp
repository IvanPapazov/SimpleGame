#include "stdafx.h"
#include "GameObjectManager.h"
#include <Game/Player.h>
#include <Game/Enemy.h>
#include <Game/Pathways.h>
#include <Game/EnemyCannonBall.h>


GameObjectManager& GameObjectManager::getInstance()
{
    static GameObjectManager ms_Instance;
    return ms_Instance;
}

void GameObjectManager::AddGameObject(std::unique_ptr<GameObject> obj)
{
    GameObject* rawPtr = obj.get();
    if (typeid(*obj) == typeid(Player) || typeid(*obj) == typeid(Enemy) ||
        typeid(*obj) == typeid(Pathways) || typeid(*obj) == typeid(EnemyCannonBall))
    {     
        m_EventSystem->RegisterCollisionEvent(rawPtr);
    }
    if (typeid(*obj) == typeid(Player) || typeid(*obj) == typeid(Enemy))
    {
        m_EventSystem->RegisterGravityEvents(rawPtr);
    }
    if ( typeid(*obj) == typeid(Enemy))
    {
        m_EventSystem->RegisterCreateFireBallEvents(rawPtr);
    }
    if (obj) {
        int id = obj->GetId();
        m_gameObjects[id] = std::move(obj);
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
    m_gameObjects.erase(id);
}

void GameObjectManager::RemoveAllGameObject()
{
    m_gameObjects.clear(); 
}

GameObject* GameObjectManager::GetGameObject(int id) const
{
    auto it = m_gameObjects.find(id);
    if (it != m_gameObjects.end())
    {
        return it->second.get();
    }
    return nullptr;
}

GameObject* GameObjectManager::GetPlayer() const {
    for (const auto& [id, obj] : m_gameObjects) {
        if (dynamic_cast<Player*>(obj.get())) {
            return obj.get();
        }
    }
    return nullptr;
}
