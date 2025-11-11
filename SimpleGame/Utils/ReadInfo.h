#pragma once
#include <unordered_map>
#include <Game/Game.h>
#include <Game/GameObject.h>
#include <Components/RigidBodyComponent.h>
#include <Components/CollisionComponent.h>
#include <Components/HealthComponent.h>
#include <Components/RenderComponent.h>
#include <Components/MovementComponent.h>
#include <Components/LevelTransitionComponent.h>
#include <Components/CannonFireAIComponent.h>
#include <Components/AIComponent.h>

class ReadInfo
{
private:

	RigidBodyComponent* CreateRigidBodyComponent(Json::Value& data);
	RenderComponent* CreateRenderComponent(Json::Value& data);
	CollisionComponent* CreateCollisionComponent(Json::Value& data);
	HealthComponent* CreateHealthComponent(Json::Value& data);
	MovementComponent* CreateMovementComponent(Json::Value& data);
	LevelTransitionComponent* CreateLevelTransitionComponent(Json::Value& data);
	AIComponent* CreateEnemyRunAIComponent(Json::Value& data);
	AIComponent* CreateCannonFireAIComponent(Json::Value& data);
	AIComponent* CreateRampMovementComponent(Json::Value& data);
public:
	std::unordered_map<int, GameObject*> ReadInfoPlayer(const std::string& levelName);
	std::unordered_map<int, GameObject*> ReadInfoEnemy(const std::string& levelName);
	std::unordered_map<int, GameObject*> ReadInfoTerrain(const std::string& levelName);
	std::unordered_map<int, GameObject*> ReadInfoHearts();
	std::unordered_map<int, GameObject*> ReadInfoPathways(const std::string& levelName);
	void ReadTextures();
	void ReadSpriteData();
};