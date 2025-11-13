#include "stdafx.h"
#include <SDL.h>
#include "Core/GameObjectManager.h"
#include <Game/GameObject.h>
#include <Core/Component.h>
#include <Components/CollisionComponent.h>
#include <Components/RigidBodyComponent.h>
#include <Components/MovementComponent.h>
#include <Components/AIComponent.h>
#include <Game/Enemy.h>
#include <Game/Terrain.h>
#include <Game/Player.h>
#include <Game/Pathways.h>
#include <Components/LevelTransitionComponent.h>
#include <Core/QuadTree.h>
#include <Game/Game.h>
#include <Events/Event.h>
#include <Events/EventHandler.h>

extern Game& game;
extern GameObjectManager& gameObjectManager;

void CollisionComponent::SetHit(bool value) {
    if (value && !m_Hit) {
        m_HitPast = true;
    }
    else if (!value) {
        m_HitPast = false;
    }
    m_Hit = value;
}

void CollisionComponent::Update()
{
    GameObject* owner = GetOwner();
    if (!owner || typeid(*owner) == typeid(Terrain)) return;

    auto* colA = owner->GetComponent<CollisionComponent>();
    auto* rbA = owner->GetComponent<RigidBodyComponent>();
    if (!colA || !rbA) return;

    colA->m_X = rbA->getPosition().x;
    colA->m_Y = rbA->getPosition().y;

    colA->m_BottomCollision = true;
    if (typeid(*owner) == typeid(Player)) {
        colA->m_LeftCollision = true;
        colA->m_RightCollision = true;
        colA->m_HitDetected = false;
    }

    Rect searchArea{
        colA->m_X - 200,
        colA->m_Y - 200,
        colA->m_Width + 400,
        colA->m_Height + 400
    };

    std::vector<GameObject*> nearby;
    game.GetQuadTree()->Query(searchArea, nearby);

    for (GameObject* b : nearby) {
        if (!b || b->GetId() == owner->GetId()) continue;

        auto* colB = b->GetComponent<CollisionComponent>();
        if (!colB) continue;

        if (typeid(*owner) == typeid(Player)) {
            colB->SetDoorCollision(false);
        }

        if (CheckCollision(colA, colB)) {

            CollisionEvent event(owner, b);
            EventHandler::getInstance().Notify(event, owner);
        }
    }

    if (!m_HitDetected) {
        colA->SetHit(false); // TODO...
    }
}

bool CollisionComponent::CheckCollision(CollisionComponent* a, CollisionComponent* b)
{
    return (a->m_X < b->m_X + b->m_Width &&
        a->m_X + a->m_Width > b->m_X &&
        a->m_Y < b->m_Y + b->m_Height &&
        a->m_Y + a->m_Height > b->m_Y);
}
