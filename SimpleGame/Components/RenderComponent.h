#pragma once
#include "stdafx.h"
#include <SDL.h>
#include "Core/Component.h"
#include "SDL_image.h"

class RenderComponent : public Component
{
private:
	float m_Width, m_Height;
	const char* m_FilePath;
	SDL_Renderer* m_Renderer;
	SDL_Texture* m_Texture;
	SDL_Rect m_DestRect;
	static SDL_Texture* m_OffScreenCombinedTexture;
public:
	RenderComponent(int w, int h, SDL_Renderer* r, const char* path);
	~RenderComponent();

	void Update(GameObject* object) override;
	void CombineTextures(float x, float y);

	static SDL_Texture* GetOffScreenCombinedTexture() {
		return m_OffScreenCombinedTexture;
	}
};