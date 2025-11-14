#include "stdafx.h"
#include <unordered_map>
#include <Game/GameObject.h>
#include <Components/AIComponent.h>
#include <Components/CollisionComponent.h>
#include <Components/RigidBodyComponent.h>
#include <Components/CannonFireAIComponent.h>
#include <Core/ResourceManager.h>
#include <Components/RenderComponent.h>
#include <Game/Game.h>
#include <Game/Enemy.h>
#include <Game/EnemyCannonBall.h>
#include <Components/EnemyRunAIComponent.h>


extern Game& game;
extern ResourceManager& g_ResourceManager;
extern EventHandler& g_EventHandler;
extern GameObjectManager& gameObjectManager;

CannonFireAIComponent::CannonFireAIComponent(float speed)
	:AIComponent(speed) {}

void CannonFireAIComponent::Update()
{
	RenderComponent* renderOwner = GetOwner()->GetComponent<RenderComponent>();
	//g_ResourceManager.setCurrentState(renderOwner->GetTextureId(), "Idle");
	
	GameObject* owner = GetOwner();
	m_TransitionTimer.Update(1500, [&]() {
		g_ResourceManager.setCurrentState(renderOwner->GetTextureId(), "Fire");
		g_EventHandler.Notify(BallEvent(owner), owner);
		});

	Enemy* enemy = dynamic_cast<Enemy*>(GetOwner());
	for (auto object : enemy->cannonBalls)
	{
		if (typeid(*object) == typeid(EnemyCannonBall))
		{
			RenderComponent* render = object->GetComponent<RenderComponent>();
			RigidBodyComponent* rbA = object->GetComponent<RigidBodyComponent>();
			CollisionComponent* result = object->GetComponent<CollisionComponent>();

			Vec2 velocity = rbA->getVelocity();
			if (GetOwner() == enemyBall && GetOwner()->GetComponent<RenderComponent>()->GetTextureId() == 15)
			{
			velocity.x = -GetSpeed();
			}
			if (GetOwner() == enemyBall && GetOwner()->GetComponent<RenderComponent>()->GetTextureId() == 16)
			{
					velocity.x = GetSpeed();
			}
			float dt = game.GetDeltaTime();
			rbA->setVelocity(velocity + rbA->getAcceleration() * dt);
			rbA->setPosition(rbA->getPosition() + rbA->getVelocity() * dt);
			object->UpdateComponents();
		}

	}
}