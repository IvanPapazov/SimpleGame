#include "stdafx.h"

#include "../Game/GameObject.h"
#include "../Core/System.h"
#include "Components/RenderComponent.h"
#include "Components/RigidBodyComponent.h"

RenderComponent::RenderComponent(int w, int h, SDL_Renderer* r, const char* path)
    : m_Width(w), m_Height(h), m_Renderer(r), m_FilePath(path)
{
    m_DestRect = { 0, 0, w, h };

    SDL_Surface* surface = IMG_Load(m_FilePath);
    if (!surface) {
        SDL_Log("Failed to load image %s: %s", m_FilePath, IMG_GetError());
        return;
    }

    m_Texture = SDL_CreateTextureFromSurface(m_Renderer, surface);
    SDL_FreeSurface(surface);

    if (!m_Texture) {
        SDL_Log("Failed to create texture: %s", SDL_GetError());
        return;
    }
}

RenderComponent::~RenderComponent() {
    if (m_Texture) {
        SDL_DestroyTexture(m_Texture);
        m_Texture = nullptr;
    }
}

void RenderComponent::Update(GameObject* object)
{
        RigidBodyComponent* rb = object->GetComponent<RigidBodyComponent>();
        RenderComponent* render = object->GetComponent<RenderComponent>();

        if (rb && render) {
            render->m_DestRect.x = static_cast<int>(rb->getPosition().x);
            render->m_DestRect.y = static_cast<int>(rb->getPosition().y);
            SDL_RenderCopy(render->m_Renderer, render->m_Texture, nullptr, &render->m_DestRect);
        }
  
}