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
	RenderComponent(int w, int h, SDL_Renderer* r, const char* path)
		: m_Width(w), m_Height(h), m_Renderer(r), m_FilePath(path) {
		m_DestRect = { 0, 0, w, h };

		SDL_Surface* surface = IMG_Load(m_FilePath);
		if (!surface) {
			return;
		}

		m_Texture = SDL_CreateTextureFromSurface(m_Renderer, surface);
		SDL_FreeSurface(surface);

		if (!m_Texture) {
			return;
		}
	}
	~RenderComponent() {
		if (m_Texture) {
			SDL_DestroyTexture(m_Texture);
		}
	};

	void Update(GameObject* object, std::unordered_map<int, GameObject*> gameObjects) override;
};