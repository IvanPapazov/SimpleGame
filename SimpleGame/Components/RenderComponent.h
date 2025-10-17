#pragma once
#include <SDL.h>

class RenderComponent
{
private:
	float m_Width, m_Height;
	const char* m_FilePath;
	SDL_Renderer* m_Renderer;
	SDL_Texture* m_Texture;
	SDL_Rect m_DestRect;
public:
	RenderComponent(int w, int h, SDL_Renderer* r, SDL_Texture* tex, const char* path)
		: m_Width(w), m_Height(h), m_Renderer(r), m_Texture(tex), m_FilePath(path) {
		m_DestRect = { 0, 0, w, h };
	}
	~RenderComponent();

};