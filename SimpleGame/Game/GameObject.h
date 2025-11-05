#pragma once
#include "stdafx.h"
#include <unordered_map>
#include <any>
#include <typeindex>
#include "Core/Component.h"
class Component;
class GameObject
{
protected:
	int m_Id;
	
	std::unordered_map<std::type_index, Component*> m_Components;
public:
	GameObject(std::vector<Component*> comps);
	virtual ~GameObject();

	virtual void UpdateComponents() = 0;

	int GetId() const;

	void ClearComponents();
	void AddComponent(Component* component);

	template<typename T>
	T* GetComponent() {
		for (const auto& [key, comp] : m_Components) {
			T* casted = dynamic_cast<T*>(comp);
			if (casted) return casted;
		}
		return nullptr;
	}

	template<typename T>
	bool HasComponent() {
		return GetComponent<T>() != nullptr;
	}

	bool operator==(const GameObject& other) const {
		return m_Id == other.m_Id;
	}
};

