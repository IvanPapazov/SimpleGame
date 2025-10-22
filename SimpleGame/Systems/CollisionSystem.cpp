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
	bottom = true;
	for (auto& [key, b] : gameObjects) {
		{
			if (a == b) continue;

			
			CollisionComponent* colB = b->GetComponent<CollisionComponent>();
			if (CheckCollision(colA, colB))
			{
				SDL_Rect bounds;
				bounds.x = colB->m_X;
				bounds.y = colB->m_Y;
				bounds.w = colB->m_Width;
				bounds.h = colB->m_Height;
				/*const float tolerance = 0.5f;
				float dx = (colA->m_X + colA->m_Width / 2.0f) - (colB->m_X + colB->m_Width / 2.0f);
				float dy = (colA->m_Y + colA->m_Height / 2.0f) - (colB->m_Y + colB->m_Height / 2.0f);

				float combinedHalfWidths = (colA->m_Width + colB->m_Width) / 2.0f;
				float combinedHalfHeights = (colA->m_Height + colB->m_Height) / 2.0f;

				float overlapX = combinedHalfWidths - std::abs(dx);
				float overlapY = combinedHalfHeights - std::abs(dy);

				if (overlapX < overlapY && overlapX > tolerance)
				{
					if (dx > 0)
					{
						left = false;
					}
					else
					{
						right = false;
					}
				}
				else
				{
					if (dy > 0)
						top = false;
					else
						bottom = false;
				}*/


				SDL_Point bottomPointRight = {
					colA->m_X + static_cast<int>(colA->m_Width * 0.99f),
	                colA->m_Y + colA->m_Height
				};

				SDL_Point bottomPointMiddle = {
					colA->m_X + static_cast<int>(colA->m_Width * 0.5f),
					colA->m_Y + colA->m_Height
				};

				SDL_Point bottomPointLeft = {
					colA->m_X + static_cast<int>(colA->m_Width * 0.01f),
					colA->m_Y + colA->m_Height
				};

				SDL_Point pointRight = {
					colA->m_X + colA->m_Width,
					colA->m_Y + colA->m_Height * 0.99f
				};

				SDL_Point pointLeft = {
					colA->m_X,
					colA->m_Y + colA->m_Height * 0.99f
				};
				if (SDL_PointInRect(&bottomPointMiddle, &bounds) || SDL_PointInRect(&bottomPointRight, &bounds) || SDL_PointInRect(&bottomPointLeft, &bounds))
				{
					bottom = false;
				}

				if (SDL_PointInRect(&pointRight, &bounds))
				{
					right = false;		
				}
				else if (SDL_PointInRect(&pointLeft, &bounds))
				{
					left = false;
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
