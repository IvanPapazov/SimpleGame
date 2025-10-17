#include "stdafx.h"
#include "CollisionSystem.h"
#include <Game/GameObject.h>
#include <Core/System.h>
#include <Components/CollisionComponent.h>
#include <Components/RigidBodyComponent.h>

void CollisionSystem::Update(float deltaTime, ComponentManager* cm){
    for (GameObject a : m_GameObjects) {
        CollisionComponent* colA = a.GetComponent<CollisionComponent>();
        RigidBodyComponent* rbA = a.GetComponent<RigidBodyComponent>();

        for (GameObject b : m_GameObjects) {
            if (a == b) continue;

            CollisionComponent* colB = b.GetComponent<CollisionComponent>();
            if (CheckCollision(colA, colB)) {
                rbA.velocity = Vec2(0, 0); // Simple response
            }
        }
    }
}

bool CollisionSystem::CheckCollision(CollisionComponent* a, CollisionComponent* b) {
    return (a < b.x + b.width &&
        a.x + a.width > b.x &&
        a.y < b.y + b.height &&
        a.y + a.height > b.y);
}
