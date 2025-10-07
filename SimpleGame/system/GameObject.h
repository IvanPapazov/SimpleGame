#pragma once
#include <SDL.h>
#include "../physics.h"
#include <unordered_map>


class GameObject  {
private:
	int m_Id;
	float m_Width, m_Height, m_Weight;
	RigidBody m_RigidBody;
	SDL_Texture* m_Texture;
public:
	GameObject();
	GameObject(float width, float height, const RigidBody& rb, SDL_Texture* tex);
	~GameObject();

	int GetId() { return m_Id; }
	float GetWidth() { return m_Width; }
	float GetHeight() { return m_Height; }
	RigidBody& GetRigidBody() { return m_RigidBody; }
	SDL_Texture* GetTexture() { return m_Texture; }

	void SetWidth(float width) { m_Width = width; }
	void SetHeight(float height) { m_Height = height; }
	void SetRigidBody(const RigidBody& rb) { m_RigidBody = rb; }
	void SetTexture(SDL_Texture* tex) { m_Texture = tex; }
};
GameObject* SelectGameObjectAt(float mouseX, float mouseY, std::unordered_map<int, GameObject*> gameObjects);
GameObject* InitializeGameObject(float x, float y, float w, float h, const char* filePath);
