#include "stdafx.h"

#include "../Game/GameObject.h"
#include "../Core/System.h"
#include "Components/RenderComponent.h"
#include "Components/RigidBodyComponent.h"

void RenderComponent::Update(GameObject* object, std::unordered_map<int, GameObject*> gameObjects)
{
        RigidBodyComponent* rb = object->GetComponent<RigidBodyComponent>();
        RenderComponent* render = object->GetComponent<RenderComponent>();

        if (rb && render) {
            render->m_DestRect.x = static_cast<int>(rb->getPosition().x);
            render->m_DestRect.y = static_cast<int>(rb->getPosition().y);
            SDL_RenderCopy(render->m_Renderer, render->m_Texture, nullptr, &render->m_DestRect);
        }
  
}