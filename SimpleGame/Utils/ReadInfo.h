#pragma once
#include <unordered_map>
#include <memory>
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
    std::unique_ptr<RigidBodyComponent> CreateRigidBodyComponent(Json::Value& data);
    std::unique_ptr<RenderComponent> CreateRenderComponent(Json::Value& data);
    std::unique_ptr<CollisionComponent> CreateCollisionComponent(Json::Value& data);
    std::unique_ptr<HealthComponent> CreateHealthComponent(Json::Value& data);
    std::unique_ptr<MovementComponent> CreateMovementComponent(Json::Value& data);
    std::unique_ptr<LevelTransitionComponent> CreateLevelTransitionComponent(Json::Value& data);
    std::unique_ptr<AIComponent> CreateEnemyRunAIComponent(Json::Value& data);
    std::unique_ptr<AIComponent> CreateCannonFireAIComponent(Json::Value& data);
    std::unique_ptr<AIComponent> CreateRampMovementComponent(Json::Value& data);

public:
    void ReadTextures();
    void ReadSpriteData();
    void ReadInfoBackground();
    std::unordered_map<int, std::unique_ptr<GameObject>> ReadInfoHearts();
    std::unordered_map<int, std::unique_ptr<GameObject>> ReadInfoPlayer(const std::string& levelName);
    std::unordered_map<int, std::unique_ptr<GameObject>> ReadInfoEnemy(const std::string& levelName);
    std::unordered_map<int, std::unique_ptr<GameObject>> ReadInfoTerrain(const std::string& levelName);
    std::unordered_map<int, std::unique_ptr<GameObject>> ReadInfoPathways(const std::string& levelName);
    std::unordered_map<int, std::unique_ptr<GameObject>> ReadInfoDoors(const std::string& levelName);
};
