#include "stdafx.h"
#include "EventSystem.h"
#include <Events/Event.h>
#include <Game/Player.h>
#include <Game/Enemy.h>
#include <Game/Pathways.h>
#include <Components/LevelTransitionComponent.h>

extern EventHandler& g_EventHandler;
void EventSystem::RegisterEvents(GameObject* object) {
    g_EventHandler.Subscribe<CollisionEvent>(object, [object](const Event& e) {
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

        if (typeid(*a) == typeid(Player) && typeid(*b) == typeid(Enemy)) {
            colA->SetHit(true);
            colA->SetHitDetected(true);
            return;
        }
        if (typeid(*a) == typeid(Player) && typeid(*b) == typeid(Pathways) && b->HasComponent<LevelTransitionComponent>()) {
            colB->SetDoorCollision(true);
            return;
        }

        if (typeid(*b) == typeid(Player) && typeid(*a) == typeid(Pathways)&& !colB->TopCollision())
        {
            colA->SetTopCollision(false);
            colA->SetBottomCollision(true);
        }


        if (typeid(*b) != typeid(Player))
        {
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
        }
        });
}
