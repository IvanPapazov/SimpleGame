#include "stdafx.h"
#include "EventSystem.h"
#include <Events/Event.h>
#include <Game/Player.h>
#include <Game/Enemy.h>
#include <Game/Pathways.h>
#include <Components/LevelTransitionComponent.h>
#include <Game/Door.h>
#include <iostream>
#include <Game/EnemyCannonBall.h>
#include <Game/Terrain.h>
#include <Core/ResourceManager.h>
#include <Game/Game.h>

extern EventHandler& g_EventHandler;
extern GameObjectManager& gameObjectManager;
extern Game& game;
extern ResourceManager& g_ResourceManager;

void EventSystem::RegisterCollisionEvent(GameObject* object) {
	g_EventHandler.Subscribe<CollisionEvent>(
		object,
		[object](const Event& e) {

			const auto& collision = static_cast<const CollisionEvent&>(e);
			GameObject* a = collision.objectA;
			auto* colA = a->GetComponent<CollisionComponent>();

			colA->SetHit(true);
			colA->SetHitDetected(true);
		},
		[](const Event& e) {
			const auto& collision = static_cast<const CollisionEvent&>(e);
			if (typeid(*collision.objectA) == typeid(Player) && (typeid(*collision.objectB) == typeid(Enemy) || typeid(*collision.objectB) == typeid(EnemyCannonBall)))
				return true;
			return false;
		});

	g_EventHandler.Subscribe<CollisionEvent>(
		object,
		[object](const Event& e) {
			const auto& collision = static_cast<const CollisionEvent&>(e);
			collision.objectA->SetIsActive(false);
		},
		[](const Event& e) {
			const auto& collision = static_cast<const CollisionEvent&>(e);
			if (typeid(*collision.objectA) == typeid(EnemyCannonBall) && typeid(*collision.objectB) == typeid(Terrain))
				return true;
			return false;
		});

	g_EventHandler.Subscribe<CollisionEvent>(
		object,
		[object](const Event& e) {

			const auto& collision = static_cast<const CollisionEvent&>(e);
			GameObject* b = collision.objectB;
			auto* colB = b->GetComponent<CollisionComponent>();
			colB->SetDoorCollision(true);

		},
		[](const Event& e) {
			const auto& collision = static_cast<const CollisionEvent&>(e);
			if (typeid(*collision.objectA) == typeid(Player) && typeid(*collision.objectB) == typeid(Door))
				return true;
			return false;
		});

	g_EventHandler.Subscribe<CollisionEvent>(
		object,
		[object](const Event& e) {

			const auto& collision = static_cast<const CollisionEvent&>(e);
			GameObject* a = collision.objectA;
			auto* colA = a->GetComponent<CollisionComponent>();
			if (colA->TopCollision())
			{
				colA->SetTopCollision(false);
			}
			else
			{
				colA->SetTopCollision(true);
			}
			if (colA->BottomCollision())
			{
				colA->SetBottomCollision(false);
			}
			else
			{
				colA->SetBottomCollision(true);
			}
		},
		[](const Event& e) {
			const auto& collision = static_cast<const CollisionEvent&>(e);
			GameObject* b = collision.objectB;
			auto* colB = b->GetComponent<CollisionComponent>();
			if (typeid(*collision.objectA) == typeid(Pathways) && typeid(*collision.objectB) == typeid(Player) && !colB->TopCollision() && colB->BottomCollision())
				return true;
			return false;
		});

	g_EventHandler.Subscribe<CollisionEvent>(
		object,
		[object](const Event& e) {

			const auto& collision = static_cast<const CollisionEvent&>(e);
			GameObject* a = collision.objectA;
			auto* rb = a->GetComponent<RigidBodyComponent>();
			rb->setPosition(rb->getPosition() - Vec2(0, 1));
		},
		[](const Event& e) {
			const auto& collision = static_cast<const CollisionEvent&>(e);
			GameObject* b = collision.objectB;
			auto* colB = b->GetComponent<CollisionComponent>();
			if (typeid(*collision.objectA) == typeid(Player) && typeid(*collision.objectB) == typeid(Pathways) && colB->TopCollision())
				return true;
			return false;
		});

	g_EventHandler.Subscribe<CollisionEvent>(
		object,
		[object](const Event& e) {
			const auto& collision = static_cast<const CollisionEvent&>(e);
			GameObject* a = collision.objectA;
			auto* colA = a->GetComponent<CollisionComponent>();
			GameObject* b = collision.objectB;
			auto* colB = b->GetComponent<CollisionComponent>();

			SDL_Rect bounds = {
				static_cast<int>(colB->GetX()),
				static_cast<int>(colB->GetY()),
				static_cast<int>(colB->GetWidth()),
				static_cast<int>(colB->GetHeight()) };

			//bottom
			for (int x = 1; x < static_cast<int>(colA->GetWidth() - 1); ++x) {
				SDL_Point pt = { static_cast<int>(colA->GetX() + x), static_cast<int>(colA->GetY() + colA->GetHeight()) };
				if (SDL_PointInRect(&pt, &bounds)) {
					colA->SetBottomCollision(false);
					colA->SetTopCollision(true);
					break;
				}
			}

			//top
			for (int x = 1; x < static_cast<int>(colA->GetWidth()) - 1; ++x) {
				SDL_Point pt = { static_cast<int>(colA->GetX() + x), static_cast<int>(colA->GetY()) };
				if (SDL_PointInRect(&pt, &bounds)) {
					colA->SetTopCollision(false);
					colA->SetBottomCollision(true);
					break;
				}
			}

			//left
			for (int y = 1; y < static_cast<int>(colA->GetHeight()) - 1; ++y) {
				SDL_Point pt = { static_cast<int>(colA->GetX()), static_cast<int>(colA->GetY() + y) };
				if (SDL_PointInRect(&pt, &bounds)) {
					colA->SetLeftCollision(false);
					colA->SetRightCollision(true);
					break;
				}
			}

			//right
			for (int y = 1; y < static_cast<int>(colA->GetHeight()) - 1; ++y) {
				SDL_Point pt = { static_cast<int>(colA->GetX() + colA->GetWidth()), static_cast<int>(colA->GetY() + y) };
				if (SDL_PointInRect(&pt, &bounds)) {
					colA->SetRightCollision(false);
					colA->SetLeftCollision(true);
					break;
				}
			}
		},
		[](const Event& e) {
			const auto& collision = static_cast<const CollisionEvent&>(e);
			if (typeid(*collision.objectB) != typeid(EnemyCannonBall) && typeid(*collision.objectB) != typeid(Door) && typeid(*collision.objectB) != typeid(Player))
				return true;
			return false;
		});

}

void EventSystem::RegisterGravityEvents(GameObject* object) {
	g_EventHandler.Subscribe<GravityEvent>(
		object,
		[](const Event& e) {
			const auto& gravity = static_cast<const GravityEvent&>(e);
			auto* obj = gravity.object;
			if (!obj) return;

			auto* rb = obj->GetComponent<RigidBodyComponent>();
			auto* col = obj->GetComponent<CollisionComponent>();
			if (!rb || !col) return;

			if (col->BottomCollision()) {
				Vec2 accel = rb->getAcceleration();
				accel.y = rb->GetGravityScale();
				rb->setAcceleration(accel);
			}
			else {
				Vec2 vel = rb->getVelocity();
				vel.y = 0;
				rb->setVelocity(vel);
			}
		},
		[](const Event& e) {
			const auto& collision = static_cast<const GravityEvent&>(e);
			if (typeid(*collision.object) == typeid(Player) || typeid(*collision.object) == typeid(Enemy))
				return true;
			return false;
		});
}

void EventSystem::RegisterCreateFireBallEvents(GameObject* object) {
	g_EventHandler.Subscribe<BallEvent>(
		object,
		[](const Event& e) {
			const auto& gravity = static_cast<const BallEvent&>(e);
			auto* obj = gravity.object;

			RenderComponent* renderOwner = obj->GetComponent<RenderComponent>();
			RigidBodyComponent* rbOwner = obj->GetComponent<RigidBodyComponent>();


			std::vector<std::unique_ptr<Component>> components;
			components.push_back(std::make_unique<RigidBodyComponent>(rbOwner->getPosition() + Vec2(renderOwner->GetWidth() * 0.5, renderOwner->GetHeight() * 0.3), 0.0));
			components.push_back(std::make_unique<CollisionComponent>(rbOwner->getPosition().x, rbOwner->getPosition().y, 30, 30));
			components.push_back(std::make_unique<RenderComponent>(17, 30, 30, Game::getInstance().GetRenderer()));

			auto ball = std::make_unique<EnemyCannonBall>(std::move(components));
			auto* cannonBalls = gravity.object->GetComponent<CannonFireAIComponent>();

			cannonBalls->AddCannonBall(ball.get());
			gameObjectManager.AddGameObject(std::move(ball));
		});
}

void EventSystem::RegisterCreateLevelTransitionEvents(GameObject* object) {
	g_EventHandler.Subscribe<LevelTransitionPlayerPositionEvent>(
		object,
		[](const Event& e) {
			const auto& levelTransition = static_cast<const LevelTransitionPlayerPositionEvent&>(e);
			auto* object = levelTransition.object;

			RigidBodyComponent* rbOwner = object->GetComponent<RigidBodyComponent>();

			for (const auto& [id, obj] : gameObjectManager.m_gameObjects) {
				if (typeid(*obj) == typeid(Door))
				{
					if (game.getPreviousLevel() <= game.getCurrentLevel() ) {
						RigidBodyComponent* rbObj = obj->GetComponent<RigidBodyComponent>();
						rbOwner->setPosition(Vec2(rbObj->getPosition().x + 30, rbObj->getPosition().y));
						return;
					}
					RigidBodyComponent*  rbObj = obj->GetComponent<RigidBodyComponent>();
					rbOwner->setPosition(Vec2(rbObj->getPosition().x + 30 , rbObj->getPosition().y));
				}
			}
		});
}

void EventSystem::RegisterCreateSpotlightEvents(GameObject* object) {
	/*g_EventHandler.Subscribe<SpotlightEvent>(object, [](const Event& e) {
		const auto& spotlight = static_cast<const SpotlightEvent&>(e);
		auto* obj = spotlight.object;
		if (!obj) return;

		auto* 

		SDL_Renderer* renderer = game.GetRenderer();
		int screenWidth = game.GetScreenWidth();
		int screenHeight = game.GetScreenHeight();

		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_Rect fullScreen = { 0, 0, screenWidth, screenHeight };
		SDL_RenderFillRect(renderer, &fullScreen);

		int centerX = static_cast<int>(obj->get + obj->GetWidth() / 2);
		int centerY = static_cast<int>(obj->GetY() + obj->GetHeight() / 2);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		for (int w = -spotlight.radius; w <= spotlight.radius; ++w) {
			for (int h = -spotlight.radius; h <= spotlight.radius; ++h) {
				if (w * w + h * h <= spotlight.radius * spotlight.radius) {
					SDL_RenderDrawPoint(renderer, centerX + w, centerY + h);
				}
			}
		}
		});*/

}


