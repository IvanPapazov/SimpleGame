#pragma once
#include "SDL.h"
#include "Components.h"
#include "RigidBodyComponent.h"

class DrawComponent : public Components
{
private:
	float m_Width, m_Height;
	SDL_Renderer* m_Renderer;
	SDL_Texture* m_Texture;
	RigidBodyComponent* m_RigidBodyComponent;
	const char* m_FilePath;
	const int m_ComponentId = GetUniqueComponentID();

public:
	DrawComponent(float width, float height, SDL_Renderer* renderer, RigidBodyComponent* rigidBodyComponent, const char* filePath);
	~DrawComponent();
	void Update() override;
	void Draw();

	float GetWidth() const { return m_Width; }
	float GetHeight() const { return m_Height; }
	SDL_Renderer* GetRenderer() const { return m_Renderer; }
	const char* GetFilePath() const { return m_FilePath; }

	int GetComponentId() override {
		return m_ComponentId;
	}

};

