#include "stdafx.h"
#include "GameObjectManager.h"


GameObjectManager::GameObjectManager() {

}

void GameObjectManager::AddGameObject(GameObject* obj) {
    if (obj) {
        m_gameObjects[obj->GetId()] = obj;
    }
}

//GameObject* GameObjectManager::GetGameObject(int id) const {
//    auto it = m_gameObjects.find(id);
//    if (it != m_gameObjects.end()) {
//        return it->second;
//    }
//    return nullptr;
//}
