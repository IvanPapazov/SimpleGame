#include "stdafx.h"
#include <SDL.h>
#include "Core/GameObjectManager.h"
#include <Game/GameObject.h>
#include <Core/System.h>
#include <Components/CollisionComponent.h>
#include <Components/RigidBodyComponent.h>
#include <Components/MovementComponent.h>
#include <Components/AIComponent.h>
#include <Game/Enemy.h>
#include <Game/Terrain.h>

void CollisionComponent::Update(GameObject* a, std::unordered_map<int, GameObject*> gameObjects)
{

	CollisionComponent* colA = a->GetComponent<CollisionComponent>();
	RigidBodyComponent* rbA = a->GetComponent<RigidBodyComponent>();
	if (!a->HasComponent<MovementComponent>() && !a->HasComponent<AIComponent>())
	{
		return;
	}
	colA->m_X = rbA->getPosition().x;
	colA->m_Y = rbA->getPosition().y;
	bottom = true;
	colA->hit = false;
	for (auto& [key, b] : gameObjects) {
		{
			if (a == b) continue;
			
			CollisionComponent* colB = b->GetComponent<CollisionComponent>();
			if (typeid(*b) == typeid(Terrain)) {
				if (CheckCollision(colA, colB))
				{
					SDL_Rect bounds;
					bounds.x = colB->m_X;
					bounds.y = colB->m_Y;
					bounds.w = colB->m_Width;
					bounds.h = colB->m_Height;

					//Ground collision
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

					//left and right collision
					SDL_Point pointRight = {
						colA->m_X + colA->m_Width,
						colA->m_Y + colA->m_Height * 0.9f
					};

					SDL_Point pointLeft = {
						colA->m_X,
						colA->m_Y + colA->m_Height * 0.9f
					};
					if (SDL_PointInRect(&bottomPointMiddle, &bounds) || SDL_PointInRect(&bottomPointRight, &bounds) || SDL_PointInRect(&bottomPointLeft, &bounds))
					{
						colA->bottom = false;
					}

					if (SDL_PointInRect(&pointRight, &bounds))
					{
						colA->right = false;
						colA->left = true;
						
					}
					else if (SDL_PointInRect(&pointLeft, &bounds))
					{
						colA->left = false;
						colA->right = true;
						
					}
				}
			}
			if (typeid(*b) == typeid(Enemy)) {
				if (CheckCollision(colA, colB))
				{
					colA->hit = true;
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
