#include "stdafx.h"

#include "../Game/GameObject.h"
#include "../Core/Component.h"
#include "Components/RenderComponent.h"
#include "Components/RigidBodyComponent.h"
#include <iostream>
#include <Game/Enemy.h>
#include <Core/ResourceManager.h>

SDL_Texture* RenderComponent::m_OffScreenCombinedTexture = nullptr;
extern ResourceManager& rm;

RenderComponent::RenderComponent(int id, int w, int h, SDL_Renderer* r)
	: m_TextureId(id), m_Width(w), m_Height(h), m_Renderer(r)
{
	m_DestRect = { 0, 0, w, h };
}

RenderComponent::~RenderComponent() {}


void RenderComponent::CombineTextures(int x, int y)
{

	if (!m_OffScreenCombinedTexture)
	{
		m_OffScreenCombinedTexture = SDL_CreateTexture(
			m_Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1200, 1000);

	}

	SDL_SetRenderTarget(m_Renderer, m_OffScreenCombinedTexture);

	m_DestRect.x = x;
	m_DestRect.y = y;
	SDL_RenderCopy(m_Renderer, rm.getTexture(m_TextureId), nullptr, &m_DestRect);


	SDL_SetRenderTarget(m_Renderer, nullptr);
}



void RenderComponent::Update(GameObject* object)
{
	RigidBodyComponent* rb = object->GetComponent<RigidBodyComponent>();
	RenderComponent* render = object->GetComponent<RenderComponent>();

	if (rb && render) {
		render->m_DestRect.x = static_cast<int>(rb->getPosition().x);
		render->m_DestRect.y = static_cast<int>(rb->getPosition().y);
		SDL_RenderCopy(render->m_Renderer, rm.getTexture(render->m_TextureId), rm.getSrcRect(render->m_TextureId), &render->m_DestRect);
	}


}
