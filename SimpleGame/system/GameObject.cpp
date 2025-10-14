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
	: m_Id(ms_GameObjectIdCounter) {
	ms_GameObjectIdCounter++;
}


GameObject::~GameObject()
{
	for (auto& [id, comp] : m_Components)
	{
		if (comp)
		{
			delete comp;
		}
	}
	m_Components.clear();
}

void GameObject::UpdateComponents() 
{
	for (auto& [type, comp] : m_Components) {
		if (type == typeid(GravityComponent))
		{
			comp->Update();
		}
		else if (type == typeid(DrawComponent))
		{
			comp->Update();
		}
	}
}
void GameObject::HandleAllEvents() 
{
	for (auto& [type, comp] : m_Components)
	{
			comp->HandleAllEvents();
	}
}



