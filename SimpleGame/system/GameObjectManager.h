#include <unordered_map>
#include "GameObject.h"

class GameObjectManager {
private:
    std::unordered_map<int, GameObject*> m_gameObjects;
    GameObject* m_GameObject;

public:
    GameObjectManager();
    void AddGameObject(GameObject* obj);
    GameObject* GetGameObject(int id);
    void RemoveGameObject(int id);
    void UpdateComponents();
    void HandleAllEvents(float mouseX, float mouseY);
    void SelectGameObjectAt(float mouseX, float mouseY, std::unordered_map<int, GameObject*> gameObjects);
    const std::unordered_map<int, GameObject*>& GetAll() const;
};

