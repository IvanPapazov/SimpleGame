#include <GameObject.h>
#include "../LoadTexture.h"

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


GameObject* InitializeGameObject(float x, float y, const char* filePath) {
    GameObject* object = new GameObject();
    object->SetWidth(80.0f);
    object->SetHeight(100.0f);
    object->SetRigidBody(RigidBody(x, y));
    object->SetTexture(LoadTexture(filePath));
    if (!object->GetTexture()) {
        std::cerr << "Failed to load player texture!\n";
    }
    ms_GameObjectIdCounter++;
    return object;
}

