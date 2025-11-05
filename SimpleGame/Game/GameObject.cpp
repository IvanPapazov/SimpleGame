#include "stdafx.h"
#include "GameObject.h"


static int g_Id = 1;
GameObject::GameObject(std::vector<Component*> comps)
{
	m_Id = g_Id++;
	for (Component* comp : comps) {
		AddComponent(comp);
	}
}

GameObject::~GameObject()
{
	for (auto& [id, comp] : m_Components) {
		delete comp;
	}
	m_Components.clear();
}

int GameObject::GetId() const
{
	return m_Id;
}

void GameObject::AddComponent(Component* component)
{
	component->SetOwner(this);
	m_Components[typeid(*component)] = component;
}

