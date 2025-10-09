#include "DrawComponent.h"
#include "SDL_image.h"
#include "GameObject.h"


DrawComponent::DrawComponent(float width, float height, SDL_Renderer* renderer, RigidBodyComponent* rb, const char* filePath)
	: m_Width(width), m_Height(height), m_Renderer(renderer),m_RigidBodyComponent(rb), m_FilePath(filePath) {}

void DrawComponent::Draw()
{
	SDL_Rect dest;
	dest.x = m_RigidBodyComponent->GetPosition().x;
	dest.y = m_RigidBodyComponent->GetPosition().y;
	dest.w = GetWidth();
	dest.h = GetHeight();

	SDL_Texture* m_Texture;
	SDL_Surface* m_LoadedSurface = IMG_Load(GetFilePath());
	m_Texture = SDL_CreateTextureFromSurface(GetRenderer(), m_LoadedSurface);

	SDL_QueryTexture(m_Texture, NULL, NULL, NULL, NULL);
	SDL_RenderCopy(GetRenderer(), m_Texture, NULL, &dest);
}

void DrawComponent::Update()
{
	Draw();
}


//void Blit(SDL_Texture* texture, float x, float y, float w, float h)
//{
//	SDL_Rect dest;
//	dest.x = x;
//	dest.y = y;
//	dest.w = w;
//	dest.h = h;
//
//	SDL_QueryTexture(texture, NULL, NULL, NULL, NULL);
//	SDL_RenderCopy(ms_RendererManager.GetRenderer(), texture, NULL, &dest);
//}
//SDL_Texture* DrawComponent::LoadTexture(const char* filePath)
//{
//	//RenderingManager& rendererManager = RenderingManager::getInstance();
//	SDL_Texture* m_Texture;
//	SDL_Surface* m_LoadedSurface = IMG_Load(filePath);
//	m_Texture = SDL_CreateTextureFromSurface(rendererManager.GetRenderer(), m_LoadedSurface);
//
//	return m_Texture;
//}
