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

void CollisionComponent::Update(GameObject* a)
{

	GameObjectManager& gameObjectManager = GameObjectManager::getInstance();
	CollisionComponent* colA = a->GetComponent<CollisionComponent>();
	RigidBodyComponent* rbA = a->GetComponent<RigidBodyComponent>();
	if (!a->HasComponent<MovementComponent>() && !a->HasComponent<AIComponent>())
	{
		return;
	}
	colA->m_X = rbA->getPosition().x;
	colA->m_Y = rbA->getPosition().y;
	colA->m_Bottom = true;
	colA->m_Hit = false;
	for (auto& [key, b] : gameObjectManager.m_gameObjects) {
		{
			const int id = b->GetId();
			if (a == b) continue;
			if (!b->HasComponent<CollisionComponent>())
			{
				continue;
			}
			CollisionComponent* colB = b->GetComponent<CollisionComponent>();
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

			//m_Top collision
			SDL_Point topPointRight = {
				colA->m_X + static_cast<int>(colA->m_Width * 0.99f),
				colA->m_Y
			};

			SDL_Point topPointMiddle = {
				colA->m_X + static_cast<int>(colA->m_Width * 0.5f),
				colA->m_Y
			};

			SDL_Point topPointLeft = {
				colA->m_X + static_cast<int>(colA->m_Width * 0.01f),
				colA->m_Y
			};

			//m_Left and m_Right collision
			SDL_Point pointRight = {
				colA->m_X + colA->m_Width,
				colA->m_Y + colA->m_Height * 0.9f
			};

			SDL_Point pointLeft = {
				colA->m_X,
				colA->m_Y + colA->m_Height * 0.9f
			};



			if (CheckCollision(colA, colB))
			{
				if (typeid(*b) == typeid(Enemy)) {
					colA->m_Hit = true;
				}

				if ((SDL_PointInRect(&bottomPointMiddle, &bounds) || SDL_PointInRect(&bottomPointRight, &bounds) || SDL_PointInRect(&bottomPointLeft, &bounds)) && typeid(*b) != typeid(Player))
				{
					colA->m_Bottom = false;
					colA->m_Top = true;
					rbA->setPosition(Vec2(rbA->getPosition().x, rbA->getPosition().y - 0.1));
				}
				if (SDL_PointInRect(&topPointRight, &bounds) || SDL_PointInRect(&topPointLeft, &bounds) && typeid(*b) != typeid(Player))
				{
					colA->m_Top = false;
					colA->m_Bottom = true;
					rbA->setPosition(Vec2(rbA->getPosition().x, rbA->getPosition().y + 0.1));
				}
				if (SDL_PointInRect(&pointLeft, &bounds) && typeid(*b) != typeid(Player))
				{
					colA->m_Left = false;
					colA->m_Right = true;
					rbA->setPosition(Vec2(rbA->getPosition().x + 1, rbA->getPosition().y));

				}
				if (SDL_PointInRect(&pointRight, &bounds) && typeid(*b) != typeid(Player))
				{
					colA->m_Right = false;
					colA->m_Left = true;
					rbA->setPosition(Vec2(rbA->getPosition().x - 1, rbA->getPosition().y));
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
