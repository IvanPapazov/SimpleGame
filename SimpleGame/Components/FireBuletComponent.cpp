#include "stdafx.h"
#include "FireBuletComponent.h"
#include "GameObject.h"
#include "MoveLeftRightComponent.h"
#include "RigidBodyComponent.h"
#include "DrawComponent.h"
#include "GameObjectFactory.h"

FireBuletComponent::FireBuletComponent(){}

void FireBuletComponent::HandleAllEvents() {
	Uint64 m_Now = SDL_GetPerformanceCounter();
	m_deltaTime = (float)(m_Now - m_Last) / (float)SDL_GetPerformanceFrequency();
	m_Last = m_Now;


        /*
			if (player1->GetComponent<DrawComponent>()->GetRigidBodyComponent()->GetPosition().x == -1 && player1->GetComponent<DrawComponent>()->GetRigidBodyComponent()->GetPosition().y == -1)
			{
				float x = player->GetComponent<DrawComponent>()->GetRigidBodyComponent()->GetPosition().x + player->GetComponent<DrawComponent>()->GetWidth();
				float y = player->GetComponent<DrawComponent>()->GetRigidBodyComponent()->GetPosition().y + player->GetComponent<DrawComponent>()->GetHeight() / 2;
				Vec2 v = Vec2(x, y);
				player1->GetComponent<DrawComponent>()->GetRigidBodyComponent()->SetPosition(v);
				ms_RendererManager.AddGameObject(player1);
				bullet->SetBullet(player1);
				bullet->SetDeltaTime(deltaTime);
			}
		bullet->Update();*/

	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_E])
	{
		Update();
	}
}

void FireBuletComponent::Update()
{
	Vec2 velocity = m_bulet->GetComponent<DrawComponent>()->GetRigidBodyComponent()->GetVelocity();
	velocity.x = (100000.0f) * m_deltaTime;
	Vec2 position = m_bulet->GetComponent<DrawComponent>()->GetRigidBodyComponent()->GetPosition();
	position += velocity;
	m_bulet->GetComponent<DrawComponent>()->GetRigidBodyComponent()->SetVelocity(velocity);
	m_bulet->GetComponent<DrawComponent>()->GetRigidBodyComponent()->SetPosition(position);
}
