#pragma once
#include <vector>
#include "GameObject.h"

class ComponentManager {
private:
    std::vector<GameObject*> m_gameObjects;

public:
    void RegisterGameObject(GameObject* obj) {
        m_gameObjects.push_back(obj);
    }

    /*void UpdateAll(float deltaTime) {
        for (GameObject* obj : m_gameObjects) {
            obj->UpdateComponents();
        }
    }*/

 /*   void HandleAllEvents(float deltaTime) {
        for (GameObject* obj : m_gameObjects) {
            obj->HandleEvents(deltaTime);
        }
    }*/

    /*void DrawAll(SDL_Renderer* renderer) {
        for (GameObject* obj : m_gameObjects) {
            if (DrawComponent* draw = obj->GetComponent<DrawComponent>()) {
                draw->Draw(renderer);
            }
        }
    }*/
};

