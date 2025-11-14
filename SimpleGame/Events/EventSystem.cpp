#include "stdafx.h"
#include "EventSystem.h"
#include <Events/Event.h>
#include <Game/Player.h>
#include <Game/Enemy.h>
#include <Game/Pathways.h>
#include <Components/LevelTransitionComponent.h>
#include <Game/Door.h>
#include <iostream>

extern EventHandler& g_EventHandler;
void EventSystem::RegisterCollisionEvents(GameObject* object) {
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
			if (typeid(*collision.objectA) == typeid(Player) && typeid(*collision.objectB) == typeid(Enemy))
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
			colA->SetTopCollision(false);
			colA->SetBottomCollision(true);
		}, 
		[](const Event& e) {
			const auto& collision = static_cast<const CollisionEvent&>(e);
			GameObject* b = collision.objectB;
			auto* colB = b->GetComponent<CollisionComponent>();
			if (typeid(*collision.objectA) == typeid(Pathways) && typeid(*collision.objectB) == typeid(Player) && !colB->TopCollision())
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
			if (typeid(*collision.objectB) != typeid(Door) && typeid(*collision.objectB) != typeid(Player))
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
				rb->setPosition(rb->getPosition() - Vec2(0, 0.1f));
			}
		},
		[](const Event& e) {
			const auto& collision = static_cast<const GravityEvent&>(e);
			if (typeid(*collision.object) == typeid(Player) || typeid(*collision.object) == typeid(Enemy))
				return true;
			return false;
		});
}
