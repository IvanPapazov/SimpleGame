#pragma once
#include <SDL.h>
#include <unordered_map>
#include "../Components/Components.h"


class GameObject  
{
private:
	int m_Id;
	std::unordered_map<int , Components*> m_Components;
public:
	GameObject();
	~GameObject();

	void UpdateComponents(GameObject* player);

	void AddComponent(Components* component);

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

//	int GetId() 
//	{
//		return m_Id; 
//	}
//	float GetWidth() 
//	{
//		return m_Width; 
//	}
//	float GetHeight() 
//	{
//		return m_Height; 
//	}
//	float GetMass()
//	{
//		return m_Mass;
//	}
//	RigidBody& GetRigidBody() 
//	{
//		return m_RigidBody; 
//	}
//	SDL_Texture* GetTexture() 
//	{
//		return m_Texture; 
//	}
//
//	void SetWidth(float width) 
//	{
//		m_Width = width; 
//	}
//	void SetHeight(float height) 
//	{
//		m_Height = height; 
//	}
//	void SetMass(float mass)
//	{
//		m_Mass = mass;
//	}
//	void SetRigidBody(const RigidBody& rb) 
//	{
//		m_RigidBody = rb; 
//	}
//	void SetTexture(SDL_Texture* tex) 
//	{
//		m_Texture = tex; 
//	}
};
//GameObject* SelectGameObjectAt(float mouseX, float mouseY, std::unordered_map<int, GameObject*> gameObjects);
//GameObject* InitializeGameObject(float x, float y, float w, float h,float m, const char* filePath);
