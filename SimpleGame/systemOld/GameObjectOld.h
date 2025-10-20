#pragma once
#include <SDL.h>
#include <unordered_map>

#include <typeindex>


class GameObjectOld  
{
//private:
//	int m_Id;
//	//std::unordered_map<std::type_index, Components*> m_Components;
//public:
//	GameObjectOld();
//	~GameObjectOld();
//
//	void UpdateComponents();
//	void HandleAllEvents();
//	void CheckCollision(GameObjectOld* a, GameObjectOld* b);
//
//	int GetId() const {
//		return m_Id;
//	}
//
//	template<typename T>
//	void AddComponent(T* component) {
//		static_assert(std::is_base_of<Components, T>::value);
//		m_Components[typeid(T)] = component;
//	}
//
//	template<typename T>
//	T* GetComponent() {
//		for (const auto& [key, comp] : m_Components) {
//			T* casted = dynamic_cast<T*>(comp);
//			if (casted) return casted;
//		}
//		return nullptr;
//	}
//
//	template<typename T>
//	bool HasComponent() {
//		return GetComponent<T>() != nullptr;
//	}
};
