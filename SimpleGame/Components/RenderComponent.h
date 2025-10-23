#pragma once
#include "stdafx.h"
#include <SDL.h>
#include "Core/System.h"
#include "SDL_image.h"

class RenderComponent : public System
{
private:
	float m_Width, m_Height;
	const char* m_FilePath;
	SDL_Renderer* m_Renderer;
	SDL_Texture* m_Texture;
	SDL_Rect m_DestRect;
public:
	RenderComponent(int w, int h, SDL_Renderer* r, const char* path);
	~RenderComponent();

	void Update(GameObject* object) override;
};