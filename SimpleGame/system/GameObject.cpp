#include <GameObject.h>
#include "../LoadTexture.h"
#include <RenderingManager.h>
#include <unordered_map>



static int ms_GameObjectIdCounter = 0;

GameObject::GameObject()
    : m_Id(ms_GameObjectIdCounter), m_Width(0.0f), m_Height(0.0f), m_Texture(nullptr) {
}

GameObject::GameObject(float width, float height, const RigidBody& rb, SDL_Texture* tex)
    : m_Id(ms_GameObjectIdCounter), m_Width(width), m_Height(height), m_RigidBody(rb), m_Texture(tex) {
}

GameObject::~GameObject() {
    if (m_Texture) {
        SDL_DestroyTexture(m_Texture);
        m_Texture = nullptr;
    }
}


GameObject* InitializeGameObject(float x, float y, float w, float h, const char* filePath) {
    GameObject* object = new GameObject();
    object->SetWidth(w);
    object->SetHeight(h);
    object->SetRigidBody(RigidBody(x, y));
    object->SetTexture(LoadTexture(filePath));
    if (!object->GetTexture()) {
        std::cerr << "Failed to load player texture!\n";
    }
    ms_GameObjectIdCounter++;
    return object;
}

GameObject* SelectGameObjectAt(float mouseX, float mouseY, std::unordered_map<int, GameObject*> gameObjects)
{
    for (auto& element : gameObjects) {

        SDL_Rect bounds;
        bounds.x = element.second->GetRigidBody().GetPosition().x;
        bounds.y = element.second->GetRigidBody().GetPosition().y;
        bounds.w = element.second->GetWidth();
        bounds.h = element.second->GetHeight();

        SDL_Point mousePoint = { mouseX, mouseY };
        if (SDL_PointInRect(&mousePoint, &bounds)) {
            return element.second;
        }
    }
    return nullptr;
}

