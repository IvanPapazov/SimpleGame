#include "stdafx.h"
#include "DrawComponent.h"
#include "SDL_image.h"
#include "GameObject.h"


DrawComponent::DrawComponent(float width, float height, SDL_Renderer* renderer, RigidBodyComponent* rb, const char* filePath)
	: m_Width(width), m_Height(height), m_Renderer(renderer),m_RigidBodyComponent(rb), m_FilePath(filePath) 
{
	SDL_Surface* surface = IMG_Load(GetFilePath());
	if (!surface) {
		return;
	}

	m_Texture = SDL_CreateTextureFromSurface(m_Renderer, surface);
	SDL_FreeSurface(surface);

	if (!m_Texture) {
		return;
	}
}

DrawComponent::~DrawComponent() {
	if (m_Texture) {
		SDL_DestroyTexture(m_Texture);
	}
}

void DrawComponent::Draw()
{
	SDL_Rect dest;
	dest.x = static_cast<int>(m_RigidBodyComponent->GetPosition().x);
	dest.y = static_cast<int>(m_RigidBodyComponent->GetPosition().y);
	dest.w = static_cast<int>(m_Width);
	dest.h = static_cast<int>(m_Height);

	SDL_RenderCopy(m_Renderer, m_Texture, nullptr, &dest);
}

void DrawComponent::Update()
{
	Draw();
}

