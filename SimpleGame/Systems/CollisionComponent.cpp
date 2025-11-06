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
	GameObjectManager& gameObjectManager = GameObjectManager::getInstance();
	CollisionComponent* colA = GetOwner()->GetComponent<CollisionComponent>();
	RigidBodyComponent* rbA = GetOwner()->GetComponent<RigidBodyComponent>();

	if (typeid(*GetOwner()) == typeid(Terrain))
	{
		return;
	}
	colA->m_X = rbA->getPosition().x;
	colA->m_Y = rbA->getPosition().y;
	colA->m_BottomCollision = true;
	m_HitDetected = false;
	for (auto& [key, b] : gameObjectManager.m_gameObjects)
	{
		if (GetOwner() == b || !b->HasComponent<CollisionComponent>())
			continue;

		CollisionComponent* colB = b->GetComponent<CollisionComponent>();
		colB->SetDoorCollision(false);

		if (CheckCollision(colA, colB))
		{
			if (typeid(*GetOwner()) == typeid(Player) && typeid(*b) == typeid(Pathways) && b->HasComponent<LevelTransitionComponent>()) {
				colB->SetDoorCollision(true);
				return;
			}
			HandleCollision(b, colA, colB);
		}
	}
	if (!m_HitDetected)
	{
		colA->SetHit(false);
	}
}

bool CollisionComponent::CheckCollision(CollisionComponent* a, CollisionComponent* b)
{
	return (a->m_X < b->m_X + b->m_Width &&
		a->m_X + a->m_Width > b->m_X &&
		a->m_Y < b->m_Y + b->m_Height &&
		a->m_Y + a->m_Height > b->m_Y);
}

void CollisionComponent::HandleCollision(GameObject* b,
	CollisionComponent* colA, CollisionComponent* colB)
{
	SDL_Rect bounds = { colB->m_X, colB->m_Y, colB->m_Width, colB->m_Height };


	if (typeid(*b) == typeid(Enemy)) {
		colA->SetHit(true);
		m_HitDetected = true;
		return;
	}

	CheckBottomCollision(b, colA, bounds);
	CheckTopCollision(b, colA, colB, bounds);
	CheckLeftCollision(b, colA, bounds);
	CheckRightCollision(b, colA, bounds);
}

void CollisionComponent::CheckBottomCollision(GameObject* b,
	CollisionComponent* colA, const SDL_Rect& bounds)
{
	for (int x = 1; x < static_cast<int>(colA->m_Width) - 1; ++x) {
		SDL_Point pt = { colA->m_X + x, colA->m_Y + static_cast<int>(colA->m_Height) };
		if (SDL_PointInRect(&pt, &bounds) && typeid(*b) != typeid(Player)) {
			colA->m_BottomCollision = false;
			colA->m_TopCollision = true;
			break;
		}
	}
}

void CollisionComponent::CheckTopCollision(GameObject* b,
	CollisionComponent* colA, CollisionComponent* colB, const SDL_Rect& bounds)
{
	for (int x = 1; x < static_cast<int>(colA->m_Width) - 1; ++x) {
		SDL_Point pt = { colA->m_X + x, colA->m_Y };
		if (SDL_PointInRect(&pt, &bounds) && typeid(*b) != typeid(Player))
		{
			colA->m_TopCollision = false;
			 //colA->m_BottomCollision = true;
			break;
		}

	}
}

void CollisionComponent::CheckLeftCollision(GameObject* b,
	CollisionComponent* colA, const SDL_Rect& bounds)
{
	for (int y = 1; y < static_cast<int>(colA->m_Height) - 1; ++y) {
		SDL_Point pt = { colA->m_X, colA->m_Y + y };
		if (SDL_PointInRect(&pt, &bounds) && typeid(*b) != typeid(Player)) {
			colA->m_LeftCollision = false;
			colA->m_RightCollision = true;
			break;
		}
	}
}

void CollisionComponent::CheckRightCollision(GameObject* b,
	CollisionComponent* colA, const SDL_Rect& bounds)
{
	for (int y = 1; y < static_cast<int>(colA->m_Height) - 1; ++y) {
		SDL_Point pt = { colA->m_X + static_cast<int>(colA->m_Width), colA->m_Y + y };
		if (SDL_PointInRect(&pt, &bounds) && typeid(*b) != typeid(Player)) {
			colA->m_RightCollision = false;
			colA->m_LeftCollision = true;
			break;
		}
	}
}
