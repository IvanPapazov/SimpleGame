#include "stdafx.h"
#include <SDL.h>
#include "Core/GameObjectManager.h"
#include <Game/GameObject.h>
#include <Core/System.h>
#include <Components/CollisionComponent.h>
#include <Components/RigidBodyComponent.h>
#include <Components/MovementComponent.h>

void CollisionComponent::Update(GameObject* a, std::unordered_map<int, GameObject*> gameObjects)
{

	CollisionComponent* colA = a->GetComponent<CollisionComponent>();
	RigidBodyComponent* rbA = a->GetComponent<RigidBodyComponent>();
	if (!a->HasComponent<MovementComponent>())
	{
		return;
	}

	SDL_Rect bounds;
	bounds.x = m_X;
	bounds.y = m_Y;
	bounds.w = m_Width;
	bounds.h = m_Height;

	colA->m_X = rbA->getPosition().x;
	colA->m_Y = rbA->getPosition().y;

	for (auto& [key, b] : gameObjects) {
		{
			if (a == b) continue;


			CollisionComponent* colB = b->GetComponent<CollisionComponent>();
			if (CheckCollision(colA, colB))
			{
				//const float tolerance = 0.1f;
				//float dx = (colA->m_X + colA->m_Width / 2.0f) - (colB->m_X + colB->m_Width / 2.0f);
				//float dy = (colA->m_Y + colA->m_Height / 2.0f) - (colB->m_Y + colB->m_Height / 2.0f);

				//float combinedHalfWidths = (colA->m_Width + colB->m_Width) / 2.0f;
				//float combinedHalfHeights = (colA->m_Height + colB->m_Height) / 2.0f;

				//float overlapX = combinedHalfWidths - std::abs(dx);
				//float overlapY = combinedHalfHeights - std::abs(dy);

				//if (overlapX > tolerance && overlapY > tolerance) {
				//	if (overlapX < overlapY) {
				//		// Horizontal collision
				//		if (dx > 0)
				//			left = false;   // A hit B on its left side
				//		else
				//			right = false;  // A hit B on its right side
				//	}
				//	else {
				//		if (dy > 0)
				//			top = false;    // A hit B from above
				//		else
				//			bottom = false; // A landed on B
				//	}
				//}

				if (colA->m_X < colB->m_X + colB->m_Width)
				{
					left = false;
				}
				if (colA->m_X +colA->m_Width > colB->m_X)
				{
					right = false;
				}
				if (colA->m_Y < colB->m_Y + colB->m_Height)
				{
					bottom = false;
				}
				if (colA->m_Y + colA->m_Height > colB->m_Y)
				{
					top = false;
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
