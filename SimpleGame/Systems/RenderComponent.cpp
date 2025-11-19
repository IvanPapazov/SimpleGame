#include "stdafx.h"
#include "../Game/GameObject.h"
#include "../Core/Component.h"
#include "Components/RenderComponent.h"
#include "Components/RigidBodyComponent.h"
#include <Game/Enemy.h>
#include <Core/ResourceManager.h>
#include <iostream>

SDL_Texture* RenderComponent::m_OffScreenCombinedTexture = nullptr;
extern ResourceManager& g_ResourceManager;

RenderComponent::RenderComponent(int id, float w, float h, SDL_Renderer* r)
    : m_TextureId(id), m_Width(w), m_Height(h), m_Renderer(r)
{
    m_DestRect = { 0, 0, static_cast<int>(w), static_cast<int>(h) };
}

RenderComponent::~RenderComponent() = default;

void RenderComponent::CombineTextures(int x, int y)
{
    if (!m_OffScreenCombinedTexture) {
        m_OffScreenCombinedTexture = SDL_CreateTexture(
            m_Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 2500, 1300);
    }

    SDL_SetRenderTarget(m_Renderer, m_OffScreenCombinedTexture);

    m_DestRect.x = x;
    m_DestRect.y = y;

    SDL_RenderCopy(m_Renderer, g_ResourceManager.getTexture(m_TextureId), nullptr, &m_DestRect);

    SDL_SetRenderTarget(m_Renderer, nullptr);
}

void RenderComponent::Update()
{
    GameObject* owner = GetOwner();
    if (!owner) return;

    auto* rb = owner->GetComponent<RigidBodyComponent>();
    if (!rb) return;

    m_DestRect.x = static_cast<int>(rb->getPosition().x);
    m_DestRect.y = static_cast<int>(rb->getPosition().y);

    SDL_RenderCopy(m_Renderer, g_ResourceManager.getTexture(m_TextureId), g_ResourceManager.getSrcRect(m_TextureId), &m_DestRect);
}
