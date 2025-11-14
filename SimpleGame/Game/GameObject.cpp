#include "stdafx.h"
#include "GameObject.h"
#include <iostream>
#include <Events/EventHandler.h>

static int g_Id = 1;
extern EventHandler& g_EventHandler;

GameObject::GameObject(std::vector<std::unique_ptr<Component>> comps)
    : m_Id(g_Id++) {
    for (auto& comp : comps) {
        AddComponent(std::move(comp));
    }
}

GameObject::~GameObject() {
    m_Components.clear();
    std::cout << "m_Id: " << m_Id << std::endl;
}
int GameObject::GetId() const {
    return m_Id;
}

void GameObject::AddComponent(std::unique_ptr<Component> component) {
    component->SetOwner(this);
    m_Components[typeid(*component)] = std::move(component);
}
