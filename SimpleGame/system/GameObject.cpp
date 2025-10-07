#include <GameObject.h>
#include "../loadTexture.h"

static int m_gameObjectIdCounter = 0;

GameObject::GameObject()
    : m_Id(m_gameObjectIdCounter), m_Width(0.0f), m_Height(0.0f), texture(nullptr) {
}

GameObject::GameObject(float width, float height, const Rigidbody& rb, SDL_Texture* tex)
    : m_Id(m_gameObjectIdCounter), m_Width(width), m_Height(height), rigidbody(rb), texture(tex) {
}

GameObject::~GameObject() {
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}


GameObject* initializeGameObject(float x, float y, const char* filePath) {
    GameObject* object = new GameObject();
    object->setWidth(80.0f);
    object->setHeight(100.0f);
    object->setRigidbody(Rigidbody(x, y));
    object->setTexture(loadTexture(filePath));
    if (!object->getTexture()) {
        std::cerr << "Failed to load player texture!\n";
    }
    m_gameObjectIdCounter++;
    return object;
}

