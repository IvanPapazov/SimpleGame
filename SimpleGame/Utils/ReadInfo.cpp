#include "stdafx.h"
#include "ReadInfo.h"
#include <fstream>
#include <iostream>
#include "Game/Player.h"
#include "Game/Terrain.h"
#include "Game/Door.h"
#include "Game/Enemy.h"
#include "Game/Heart.h"
#include "Game/Pathways.h"
#include <Components/EnemyRunAIComponent.h>
#include <Components/RampMovementComponent.h>
#include <Core/ResourceManager.h>
#include <Game/Game.h>

extern ResourceManager& g_ResourceManager;
extern Game& game;

std::unordered_map<int, std::unique_ptr<GameObject>> ReadInfo::ReadInfoPlayer(const std::string& levelName) {
	g_ResourceManager.loadJson("player", "jsons/PlayerFile.json");
	Json::Value root = g_ResourceManager.getJson("player");
	Json::Value playerData = root[levelName];

	std::unordered_map<int, std::unique_ptr<GameObject>> m_AllGameObject;

	for (const auto& key : playerData.getMemberNames()) {
		std::vector<std::unique_ptr<Component>> components;
		components.push_back(CreateRigidBodyComponent(playerData[key]));
		components.push_back(CreateCollisionComponent(playerData[key]));
		components.push_back(CreateMovementComponent(playerData[key]));
		components.push_back(CreateHealthComponent(playerData[key]));
		components.push_back(CreateRenderComponent(playerData[key]));

		auto obj = std::make_unique<Player>(std::move(components));
		m_AllGameObject[obj->GetId()] = std::move(obj);
	}
	return m_AllGameObject;
}

std::unordered_map<int, std::unique_ptr<GameObject>> ReadInfo::ReadInfoEnemy(const std::string& levelName) {
	g_ResourceManager.loadJson("enemy", "jsons/EnemyFile.json");
	Json::Value root = g_ResourceManager.getJson("enemy");
	Json::Value enemyData = root[levelName];

	std::unordered_map<int, std::unique_ptr<GameObject>> m_AllGameObject;

	for (const auto& key : enemyData.getMemberNames()) {
		std::vector<std::unique_ptr<Component>> components;
		components.push_back(CreateRigidBodyComponent(enemyData[key]));

		if (key.find("pig") != std::string::npos) {
			components.push_back(CreateCollisionComponent(enemyData[key]));
			components.push_back(CreateEnemyRunAIComponent(enemyData[key]));
		}
		else if (key.find("Cannon") != std::string::npos) {
			components.push_back(CreateCannonFireAIComponent(enemyData[key]));
		}

		components.push_back(CreateRenderComponent(enemyData[key]));
		auto obj = std::make_unique<Enemy>(std::move(components));
		m_AllGameObject[obj->GetId()] = std::move(obj);
	}
	return m_AllGameObject;
}

std::unordered_map<int, std::unique_ptr<GameObject>> ReadInfo::ReadInfoTerrain(const std::string& levelName) {
	g_ResourceManager.loadJson("terrain", "jsons/TerrainFile.json");
	Json::Value root = g_ResourceManager.getJson("terrain");
	Json::Value terrainData = root[levelName];

	std::unordered_map<int, std::unique_ptr<GameObject>> m_AllGameObject;

	for (const auto& groupKey : terrainData.getMemberNames()) {
		Json::Value& group = terrainData[groupKey];

		for (const auto& key : group.getMemberNames()) {
			Json::Value& node = group[key];

			if (key.find("Background") != std::string::npos) {
				auto render = CreateRenderComponent(node);
				render->CombineTextures(node["x"].asFloat(), node["y"].asFloat());
				continue;
			}

			std::vector<std::unique_ptr<Component>> components;
			components.push_back(CreateRigidBodyComponent(node));
			components.push_back(CreateCollisionComponent(node));
			components.push_back(CreateRenderComponent(node));

			auto obj = std::make_unique<Terrain>(std::move(components));
			m_AllGameObject[obj->GetId()] = std::move(obj);
		}
	}
	return m_AllGameObject;
}

std::unordered_map<int, std::unique_ptr<GameObject>> ReadInfo::ReadInfoPathways(const std::string& levelName) {
	g_ResourceManager.loadJson("pathways", "jsons/PathwaysFile.json");
	Json::Value root = g_ResourceManager.getJson("pathways");
	Json::Value pathwaysData = root[levelName];

	std::unordered_map<int, std::unique_ptr<GameObject>> m_AllGameObject;

	for (const auto& key : pathwaysData.getMemberNames()) {
		std::vector<std::unique_ptr<Component>> components;
		components.push_back(CreateRigidBodyComponent(pathwaysData[key]));
		components.push_back(CreateCollisionComponent(pathwaysData[key]));
		components.push_back(CreateRenderComponent(pathwaysData[key]));
		components.push_back(CreateRampMovementComponent(pathwaysData[key]));
		auto obj = std::make_unique<Pathways>(std::move(components));
		m_AllGameObject[obj->GetId()] = std::move(obj);
	}
	return m_AllGameObject;
}

std::unordered_map<int, std::unique_ptr<GameObject>> ReadInfo::ReadInfoDoors(const std::string& levelName) {
	g_ResourceManager.loadJson("doors", "jsons/DoorsFile.json");
	Json::Value root = g_ResourceManager.getJson("doors");
	Json::Value doorsData = root[levelName];

	std::unordered_map<int, std::unique_ptr<GameObject>> m_AllGameObject;

	for (const auto& key : doorsData.getMemberNames()) {
		std::vector<std::unique_ptr<Component>> components;
		components.push_back(CreateRigidBodyComponent(doorsData[key]));
		components.push_back(CreateCollisionComponent(doorsData[key]));
		components.push_back(CreateLevelTransitionComponent(doorsData[key]));
		components.push_back(CreateRenderComponent(doorsData[key]));

		auto obj = std::make_unique<Door>(std::move(components));
		m_AllGameObject[obj->GetId()] = std::move(obj);
	}
	return m_AllGameObject;
}

std::unordered_map<int, std::unique_ptr<GameObject>> ReadInfo::ReadInfoHearts() {
	g_ResourceManager.loadJson("hearts", "jsons/HeartsFile.json");
	Json::Value itemsData = g_ResourceManager.getJson("hearts");

	std::unordered_map<int, std::unique_ptr<GameObject>> m_AllGameObject;

	for (const auto& key : itemsData.getMemberNames()) {
		std::vector<std::unique_ptr<Component>> components;
		components.push_back(CreateRigidBodyComponent(itemsData[key]));
		components.push_back(CreateRenderComponent(itemsData[key]));

		auto obj = std::make_unique<Heart>(std::move(components));
		m_AllGameObject[obj->GetId()] = std::move(obj);
	}
	return m_AllGameObject;
}

void ReadInfo::ReadTextures() {
	g_ResourceManager.loadJson("textures", "jsons/TexturesFile.json");
	Json::Value texturesData = g_ResourceManager.getJson("textures");

	for (const auto& key : texturesData.getMemberNames()) {
		const Json::Value& node = texturesData[key];
		int id = std::stoi(key);
		std::string imagePath = node["image"].asString();
		g_ResourceManager.loadTexture(id, imagePath);
	}
}

void ReadInfo::ReadSpriteData() {
	g_ResourceManager.loadJson("sprite", "jsons/SpriteDataFile.json");
	Json::Value spriteData = g_ResourceManager.getJson("sprite");

	for (const auto& key : spriteData.getMemberNames()) {
		const Json::Value& node = spriteData[key];
		int id = std::stoi(key);

		auto sprite = std::make_unique<SpriteData>();
		sprite->m_FrameWidth = node["frameWidth"].asInt();
		sprite->m_FrameHeight = node["frameHeight"].asInt();

		const Json::Value& animationsNode = node["animations"];
		for (const auto& animName : animationsNode.getMemberNames()) {
			const Json::Value& anim = animationsNode[animName];
			sprite->m_Animations[animName] = {
				anim["startFrame"].asInt(),
				anim["frameCount"].asInt(),
				anim["frameSpeed"].asInt()
			};
		}
		g_ResourceManager.loadSpriteData(id, std::move(sprite));
	}

}
std::unique_ptr<RigidBodyComponent> ReadInfo::CreateRigidBodyComponent(Json::Value& data) {
	return std::make_unique<RigidBodyComponent>(Vec2(data["x"].asFloat(), data["y"].asFloat()), data["gravity"].asFloat());
}

std::unique_ptr<CollisionComponent> ReadInfo::CreateCollisionComponent(Json::Value& data) {
	return std::make_unique<CollisionComponent>(data["x"].asFloat(), data["y"].asFloat(), data["width"].asFloat(), data["height"].asFloat());
}

std::unique_ptr<HealthComponent> ReadInfo::CreateHealthComponent(Json::Value& data) {
	return std::make_unique<HealthComponent>(data["health"].asInt());
}

std::unique_ptr<MovementComponent> ReadInfo::CreateMovementComponent(Json::Value&) {
	return std::make_unique<MovementComponent>();
}

std::unique_ptr<RenderComponent> ReadInfo::CreateRenderComponent(Json::Value& data) {
	return std::make_unique<RenderComponent>(data["id"].asInt(), data["width"].asFloat(), data["height"].asFloat(), game.GetRenderer());
}

std::unique_ptr<LevelTransitionComponent> ReadInfo::CreateLevelTransitionComponent(Json::Value& data) {
	return std::make_unique<LevelTransitionComponent>(data["level"].asString());
}

std::unique_ptr<AIComponent> ReadInfo::CreateEnemyRunAIComponent(Json::Value& data) {
	return std::make_unique<EnemyRunAIComponent>(data["speed"].asFloat());
}

std::unique_ptr<AIComponent> ReadInfo::CreateCannonFireAIComponent(Json::Value& data) {
	return std::make_unique<CannonFireAIComponent>(data["speed"].asFloat());
}

std::unique_ptr<AIComponent> ReadInfo::CreateRampMovementComponent(Json::Value& data) {
	return std::make_unique<RampMovementComponent>(data["speed"].asFloat());
}


