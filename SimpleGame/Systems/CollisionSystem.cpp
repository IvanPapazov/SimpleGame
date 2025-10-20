#include "stdafx.h"
#include "Core/GameObjectManager.h"
#include <Game/GameObject.h>
#include <Core/System.h>
#include <Components/CollisionComponent.h>
#include <Components/RigidBodyComponent.h>

void CollisionComponent::Update()
{
    for (auto& [key, a] : gom->m_gameObjects) {
        
        CollisionComponent* colA = a->GetComponent<CollisionComponent>();
        RigidBodyComponent* rbA = a->GetComponent<RigidBodyComponent>();

        for (auto& [key, b] : gom->m_gameObjects) {
            {
                if (a == b) continue;

                CollisionComponent* colB = b->GetComponent<CollisionComponent>();
                if (CheckCollision(colA, colB))
                {
                    rbA->setVelocity(Vec2(0, 0));
                }
            }
        }
    }
}

bool CollisionComponent::CheckCollision(CollisionComponent* a, CollisionComponent* b) 
{
    return (a->m_X < b->m_X + b->m_Width &&
        a->m_X + a->m_Width > b->m_X &&
        a->m_Y < b->m_Y + b->m_Height &&
        a->m_Y + a->m_Height > b->m_Y);
}
