#include "stdafx.h"
#include <GameObject.h>
#include <RenderingManager.h>
#include <unordered_map>
#include "../Components/Components.h"
#include "../Components/GravityComponent.h"
#include "../Components/JumpComponent.h"
#include "../Components/DrawComponent.h"


static int ms_GameObjectIdCounter = 0;

GameObject::GameObject()
    : m_Id(ms_GameObjectIdCounter){
    ms_GameObjectIdCounter++;
}


GameObject::~GameObject() 
{
    for (auto& [id, comp] : m_Components) {
        if (comp) {   
            delete comp;    
        }
    }
    m_Components.clear();
}
void GameObject::UpdateComponents(GameObject* player)
{
    if (player->HasComponent<GravityComponent>()) {
        Components* gravity = player->GetComponent<GravityComponent>();
        gravity->Update();
    }
    if (player->HasComponent<DrawComponent>()) {
        Components* draw = player->GetComponent<DrawComponent>();
        draw->Update();
    }
}

void GameObject::AddComponent(Components* component)
{
    m_Components.emplace(component->GetComponentId(), component);
    
}


GameObject* SelectGameObjectAt(float mouseX, float mouseY, std::unordered_map<int, GameObject*> gameObjects)
{
    for (auto& element : gameObjects)
    {
        SDL_Rect bounds;
        bounds.x = element.second->GetComponent<GravityComponent>()->GetRigidBodyComponent()->GetPosition().x;
        bounds.y = element.second->GetComponent<GravityComponent>()->GetRigidBodyComponent()->GetPosition().y;
        bounds.w = element.second->GetComponent<DrawComponent>()->GetWidth();
        bounds.h = element.second->GetComponent<DrawComponent>()->GetHeight();

        SDL_Point mousePoint = { mouseX, mouseY };
        if (SDL_PointInRect(&mousePoint, &bounds))
        {
            return element.second;
        }
    }
    //return nullptr;
}

