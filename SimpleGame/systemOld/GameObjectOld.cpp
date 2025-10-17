#include "stdafx.h"
#include <unordered_map>
#include "../ComponentsOld/Components.h"
#include "../ComponentsOld/GravityComponent.h"
#include "../ComponentsOld/JumpComponent.h"
#include "../ComponentsOld/DrawComponent.h"
#include <ComponentsOld/FireBulletComponent.h>
#include <systemOld/GameObjectOld.h>


static int ms_GameObjectIdCounter = 0;

GameObjectOld::GameObjectOld()
	: m_Id(ms_GameObjectIdCounter) {
	ms_GameObjectIdCounter++;
}


GameObjectOld::~GameObjectOld()
{
	for (auto& [id, comp] : m_Components)
	{
		if (comp)
		{
			delete comp;
		}
	}
	m_Components.clear();
}

void GameObjectOld::UpdateComponents() 
{
	for (auto& [type, comp] : m_Components) {
		if (type == typeid(GravityComponent))
		{
			comp->Update();
		}
		else if (type == typeid(DrawComponent))
		{
			comp->Update();
		}
		else if (type == typeid(FireBulletComponent))
		{
			comp->Update();
		}
	}
}
void GameObjectOld::HandleAllEvents() 
{
	for (auto& [type, comp] : m_Components)
	{
			comp->HandleAllEvents();
	}
}

void GameObjectOld::CheckCollision(GameObjectOld* a, GameObjectOld* b) {
    auto* rb = a->GetComponent<GravityComponent>()->GetRigidBodyComponent();
    auto* rbOther = b->GetComponent<DrawComponent>()->GetRigidBodyComponent();

    float ax = rb->GetPosition().x;
    float ay = rb->GetPosition().y;
    float aw = a->GetComponent<DrawComponent>()->GetWidth();
    float ah = a->GetComponent<DrawComponent>()->GetHeight();

    float bx = rbOther->GetPosition().x;
    float by = rbOther->GetPosition().y;
    float bw = b->GetComponent<DrawComponent>()->GetWidth();
    float bh = b->GetComponent<DrawComponent>()->GetHeight();

    float x = rb->GetVelocity().x;
    float y = rb->GetVelocity().y;

    float overlapLeft = (ax + aw) - bx;
    float overlapRight = (bx + bw) - ax;
    float overlapTop = (ay + ah) - by;
    float overlapBottom = (by + bh) - ay;

    float minOverlapX = std::min(overlapLeft, overlapRight);
    float minOverlapY = std::min(overlapTop, overlapBottom);

    if (minOverlapX < minOverlapY) {
        if (ax < bx && x > 0) {
            x = 0;
        }
        else if (ax > bx && x < 0) {
            x = 0;
        }
    }
    else {

        if (ay < by && y > 0) {
            y = 0; 
        }
        else if (ay > by && y < 0) {
            y = 0; 
        }
    }
    Vec2 v = Vec2(x, y);
    rb->SetVelocity(v);
}


