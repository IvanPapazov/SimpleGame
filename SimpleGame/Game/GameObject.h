#pragma once
#include "stdafx.h"
#include <unordered_map>
#include <any>
#include <typeindex>
#include "Core/System.h"

static int g_Id = 1;
class GameObject
{
protected:
	int m_Id;
	std::unordered_map<std::type_index, System*> m_Components;
public:
	GameObject(std::vector<System*> comps) {
		m_Id = g_Id;
		g_Id++;
		for (System* comp : comps) {
			AddComponent(comp);
		}
	}
	~GameObject();

	virtual void UpdateComponents(GameObject* obj, std::unordered_map<int, GameObject*> gameObjects) = 0;

	int GetId() const {
		return m_Id;
	}

	void AddComponent(System* component) {
		m_Components[typeid(*component)] = component;
	}

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

