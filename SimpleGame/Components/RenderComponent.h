#pragma once
#include "stdafx.h"
#include <SDL.h>
#include "Core/Component.h"
#include "SDL_image.h"

class RenderComponent : public Component
{
private:
	int m_TextureId;
	float m_Width, m_Height;
	SDL_Renderer* m_Renderer;
	SDL_Rect m_DestRect;
	static SDL_Texture* m_OffScreenCombinedTexture;
public:
	RenderComponent(int id, int w, int h, SDL_Renderer* r);
	~RenderComponent();

	void Update() override;
	void CombineTextures(int x, int y);

	int GetTextureId() const {
		return m_TextureId;
	}

	static SDL_Texture* GetOffScreenCombinedTexture() {
		return m_OffScreenCombinedTexture;
	}
};