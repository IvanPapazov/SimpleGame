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
#include <Components/EnemyRunAIComponent.h>


extern Game& game;
extern ResourceManager& g_ResourceManager;
extern GameObjectManager& gameObjectManager;

CannonFireAIComponent::CannonFireAIComponent(float speed)
	:AIComponent(speed) {}

void CannonFireAIComponent::Update()
{
	//RenderComponent* renderOwner = GetOwner()->GetComponent<RenderComponent>();
	//RigidBodyComponent* rbOwner = GetOwner()->GetComponent<RigidBodyComponent>();
	//g_ResourceManager.setCurrentState(renderOwner->GetTextureId(), "Fire");
	//m_TransitionTimer.Update(1500, [&]() {
	//	Enemy* ball = new Enemy({
	//		new RigidBodyComponent(rbOwner->getPosition() + Vec2(renderOwner->GetWidth() * 0.3,renderOwner->GetHeight() * 0.3)),
	//		new RenderComponent(17, 30, 30, Game::getInstance().GetRenderer()),
	//		new CollisionComponent(rbOwner->getPosition().x,rbOwner->getPosition().y,30,30)
	//		});

	//	m_Amopu
	//	gameObjectManager.AddGameObject(ball);
	//	});


	//for (auto& [key, object] : m_Amo)
	//{
	//	/*if (typeid(*object) == typeid(Enemy) && !object->HasComponent<CannonFireAIComponent>() && !object->HasComponent<EnemyRunAIComponent>())
	//	{*/
	//		RenderComponent* render = object->GetComponent<RenderComponent>();
	//		RigidBodyComponent* rbA = object->GetComponent<RigidBodyComponent>();
	//		CollisionComponent* result = object->GetComponent<CollisionComponent>();
	//		if (result->IsHit())
	//		{
	//			object->~GameObject();
	//		}

	//		Vec2 velocity = rbA->getVelocity();
	//		if (GetOwner()->GetComponent<RenderComponent>()->GetTextureId() == 15)
	//		{
	//			velocity.x = -GetSpeed();
	//		}
	//		else
	//		{
	//			velocity.x = GetSpeed();
	//		}
	//		rbA->setVelocity(velocity);
	//		rbA->setPosition(rbA->getPosition() + rbA->getVelocity() * game.GetDeltaTime());
	//	
	//}
}