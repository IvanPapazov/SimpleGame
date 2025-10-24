#pragma once
#include <unordered_map>
#include <Game/Game.h>
#include <Game/GameObject.h>
#include <Components/RigidBodyComponent.h>
#include <Components/CollisionComponent.h>
#include <Components/HealthComponent.h>
#include <Components/RenderComponent.h>
#include <Components/MovementComponent.h>
#include <Components/AIComponent.h>

class ReadInfo
{
private:

	RigidBodyComponent* CreateRigidBodyComponent(Json::Value& data);
	RenderComponent* CreateRenderComponent(Json::Value& data);
	CollisionComponent* CreateCollisionComponent(Json::Value& data);
	HealthComponent* CreateHealthComponent(Json::Value& data);
	MovementComponent* CreateMovementComponent(Json::Value& data);
	AIComponent* CreateAIComponent(Json::Value& data);
public:
	std::unordered_map<int, GameObject*> ReadInfoPlayer();
	std::unordered_map<int, GameObject*> ReadInfoEnemy();
	std::unordered_map<int, GameObject*> ReadInfoTerrain();
	std::unordered_map<int, GameObject*> ReadInfoItems();
};