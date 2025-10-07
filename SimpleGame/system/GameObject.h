#pragma once
#include <SDL.h>
#include "../physics.h"

class GameObject {
private:
	int m_Id;
	float m_Width, m_Height;
	Rigidbody rigidbody;
	SDL_Texture* texture;
public:
	GameObject();
	GameObject(float width, float height, const Rigidbody& rb, SDL_Texture* tex);
	~GameObject();

	int getId() { return m_Id; }
	float getWidth() { return m_Width; }
	float getHeight() { return m_Height; }
	Rigidbody& getRigidbody() { return rigidbody; }
	SDL_Texture* getTexture() { return texture; }

	void setId(int id) { m_Id = id; }
	void setWidth(float width) { m_Width = width; }
	void setHeight(float height) { m_Height = height; }
	void setRigidbody(const Rigidbody& rb) { rigidbody = rb; }
	void setTexture(SDL_Texture* tex) { texture = tex; }
};
GameObject* initializeGameObject(float x, float y, const char* filePath);
