#include "stdafx.h"
#include "ReadInfo.h"
#include <fstream>
#include <iostream>
#include "Game/Player.h"
#include "Game/Terrain.h"
#include "Game/Enemy.h"
#include "Game/Heart.h"
#include <Components/EnemyRunAIComponent.h>
#include <Components/RampMovementComponent.h>
#include <Core/ResourceManager.h>

ResourceManager& rm = ResourceManager::getInstance();
std::unordered_map<int, GameObject*> ReadInfo::ReadInfoPlayer()
{
	rm.loadJson("player", "images/PlayerFile.json");
	Json::Value playerData = rm.getJson("player");

	std::unordered_map<int, GameObject*> m_AllGameObject;

	for (const auto& key : playerData.getMemberNames())
	{
		Player* obj = new Player({
			CreateRigidBodyComponent(playerData[key]),
			CreateCollisionComponent(playerData[key]),
			CreateHealthComponent(playerData[key]),
			CreateMovementComponent(playerData[key]),
			CreateRenderComponent(playerData[key])
			});

		m_AllGameObject[obj->GetId()] = obj;
	}
	return m_AllGameObject;
}

std::unordered_map<int, GameObject*> ReadInfo::ReadInfoEnemy()
{
	rm.loadJson("enemy", "images/EnemyFile.json");
	Json::Value enemyData = rm.getJson("enemy");

	std::unordered_map<int, GameObject*> m_AllGameObject;
	for (const auto& key : enemyData.getMemberNames())
	{
		Enemy* obj = new Enemy({
			CreateRigidBodyComponent(enemyData[key]),
			CreateCollisionComponent(enemyData[key]),
			CreateEnemyRunAIComponent(enemyData[key]),
			CreateRenderComponent(enemyData[key])
			});

		m_AllGameObject[obj->GetId()] = obj;
	}
	return m_AllGameObject;
}

std::unordered_map<int, GameObject*> ReadInfo::ReadInfoTerrain()
{
	rm.loadJson("terrain", "images/TerrainFile.json");
	Json::Value terrainData = rm.getJson("terrain");

	std::unordered_map<int, GameObject*> m_AllGameObject;

	for (const auto& key : terrainData.getMemberNames())
	{
		Terrain* obj;
		if (key.find("Background") != std::string::npos)
		{
			const Json::Value& node = terrainData[key];
			std::cout << key << std::endl;
			RenderComponent* comp = CreateRenderComponent(terrainData[key]);
			float x = node["x"].asInt();
			float y = node["y"].asInt();
			comp->CombineTextures(x, y);
			continue;
		}
		else if (key.find("Mechanical") != std::string::npos)
		{
			obj = new Terrain({
				  CreateRigidBodyComponent(terrainData[key]),
				  CreateCollisionComponent(terrainData[key]),
				  CreateRenderComponent(terrainData[key]),
				  CreateRampMovementComponent(terrainData[key])
				});
		}
		else
		{
			obj = new Terrain({
				  CreateRigidBodyComponent(terrainData[key]),
				  CreateCollisionComponent(terrainData[key]),
				  CreateRenderComponent(terrainData[key])
				});
		}
		m_AllGameObject[obj->GetId()] = obj;
	}

	return m_AllGameObject;
}

std::unordered_map<int, GameObject*> ReadInfo::ReadInfoItems()
{
	rm.loadJson("items", "images/ItemsFile.json");
	Json::Value itemsData = rm.getJson("items");

	std::unordered_map<int, GameObject*> m_AllGameObject;


	for (const auto& key : itemsData.getMemberNames())
	{
		Heart* obj = new Heart({
			   CreateRigidBodyComponent(itemsData[key]),
			   CreateRenderComponent(itemsData[key])
			});
		m_AllGameObject[obj->GetId()] = obj;
	}

	return m_AllGameObject;
}

void ReadInfo::ReadTextures()
{
	rm.loadJson("textures", "images/TexturesFile.json");
	Json::Value texturesData = rm.getJson("textures");

	for (const auto& key : texturesData.getMemberNames())
	{
		const Json::Value& node = texturesData[key];
		int id = std::stoi(key);
		std::string imagePath = node["image"].asString();
		rm.loadTexture(id, imagePath);
	}

}

void ReadInfo::ReadSpriteData()
{
	rm.loadJson("sprite", "images/SpriteDataFile.json");
	Json::Value spriteData = rm.getJson("sprite");

	for (const auto& key : spriteData.getMemberNames())
	{
		const Json::Value& node = spriteData[key];
		int id = std::stoi(key);

		SpriteData* spriteData = new SpriteData();
		spriteData->m_FrameWidth = node["frameWidth"].asInt();
		spriteData->m_FrameHeight = node["frameHeight"].asInt();

		const Json::Value& animationsNode = node["animations"];
		for (const auto& animName : animationsNode.getMemberNames())
		{
			const Json::Value& anim = animationsNode[animName];
			spriteData->m_Animations[animName] = {
				anim["startFrame"].asInt(),
				anim["frameCount"].asInt(),
				anim["frameSpeed"].asInt()
			};
		}
		rm.loadSpriteData(id, spriteData);
	}

}

RigidBodyComponent* ReadInfo::CreateRigidBodyComponent(Json::Value& data)
{
	RigidBodyComponent* rb = new RigidBodyComponent(Vec2(data["x"].asFloat(), data["y"].asFloat()));
	return rb;
}
CollisionComponent* ReadInfo::CreateCollisionComponent(Json::Value& data)
{
	CollisionComponent* collision = new CollisionComponent(data["x"].asFloat(), data["y"].asFloat(), data["width"].asFloat(), data["height"].asFloat());
	return collision;
}
HealthComponent* ReadInfo::CreateHealthComponent(Json::Value& data)
{
	HealthComponent* health = new HealthComponent(data["health"].asInt());
	return health;
}
MovementComponent* ReadInfo::CreateMovementComponent(Json::Value& data)
{
	MovementComponent* movement = new MovementComponent();
	return movement;
}
RenderComponent* ReadInfo::CreateRenderComponent(Json::Value& data)
{
	RenderComponent* render = new RenderComponent(data["id"].asInt(),data["width"].asFloat(), data["height"].asFloat(),
		Game::getInstance().GetRenderer());
	return render;
}
AIComponent* ReadInfo::CreateEnemyRunAIComponent(Json::Value& data)
{
	return new EnemyRunAIComponent(data["speed"].asInt());
}
AIComponent* ReadInfo::CreateRampMovementComponent(Json::Value& data)
{
	return new RampMovementComponent(data["speed"].asInt());
}
