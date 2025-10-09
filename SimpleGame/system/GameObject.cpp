#include <GameObject.h>
#include <RenderingManager.h>
#include <unordered_map>
#include "../Components/Components.h"
#include "../Components/GravityComponent.h"
#include "../Components/JumpComponent.h"
#include "../Components/DrawComponent.h"


static int ms_GameObjectIdCounter = 0;

GameObject::GameObject()
    : m_Id(ms_GameObjectIdCounter){}


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
        Components* gravity = player->GetComponent<DrawComponent>();
        gravity->Update();
    }
}

void GameObject::AddComponent(Components* component)
{
    m_Components.emplace(component->GetComponentId(), component);
    
}



//GameObject* InitializeGameObject(float x, float y, float w, float h, float m, const char* filePath) 
//{
//    GameObject* object = new GameObject();
//    object->SetWidth(w);
//    object->SetHeight(h);
//    object->SetMass(m);
//    object->SetRigidBody(RigidBody(x, y));
//    object->SetTexture(LoadTexture(filePath));
//    if (!object->GetTexture()) 
//    {
//        std::cerr << "Failed to load player texture!\n";
//    }
//    ms_GameObjectIdCounter++;
//    return object;
//}
//
//GameObject* SelectGameObjectAt(float mouseX, float mouseY, std::unordered_map<int, GameObject*> gameObjects)
//{
//    for (auto& element : gameObjects) 
//    {
//        SDL_Rect bounds;
//        bounds.x = element.second->GetRigidBody().GetPosition().x;
//        bounds.y = element.second->GetRigidBody().GetPosition().y;
//        bounds.w = element.second->GetWidth();
//        bounds.h = element.second->GetHeight();
//
//        SDL_Point mousePoint = { mouseX, mouseY };
//        if (SDL_PointInRect(&mousePoint, &bounds)) 
//        {
//            return element.second;
//        }
//    }
//    return nullptr;
//}

