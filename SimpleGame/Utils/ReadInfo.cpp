#include "stdafx.h"
#include "ReadInfo.h"
#include <fstream>
#include <iostream>
#include "Game/Player.h"
#include "Game/Terrain.h"
#include "Game/Enemy.h"

std::unordered_map<int, GameObject*> ReadInfo::ReadInfoPlayer()
{
	std::ifstream file("images/PlayerFile.json", std::ios::binary);
	Json::Value root;
	Json::CharReaderBuilder builder;
	std::string errs;

	std::unordered_map<int, GameObject*> m_AllGameObject;

	if (!file.is_open())
	{
		std::cerr << "Could not open PlayerFile.json\n";
		return {};
	}

	if (Json::parseFromStream(builder, file, &root, &errs))
	{
		for (const auto& key : root.getMemberNames())
		{
			Player* obj = new Player({
				CreateRigidBodyComponent(root[key]),
				CreateCollisionComponent(root[key]),
				CreateHealthComponent(root[key]),
				CreateRenderComponent(root[key]),
				CreateMovementComponent(root[key])
				});

			m_AllGameObject[obj->GetId()] = obj;
		}
	}
	else
	{
		std::cerr << "Failed to parse JSON: " << errs << std::endl;
	}

	return m_AllGameObject;
}

std::unordered_map<int, GameObject*> ReadInfo::ReadInfoEnemy()
{
	std::ifstream file("images/EnemyFile.json", std::ios::binary);
	Json::Value root;
	Json::CharReaderBuilder builder;
	std::string errs;

	std::unordered_map<int, GameObject*> m_AllGameObject;

	if (!file.is_open())
	{
		std::cerr << "Could not open EnemyFile.json\n";
		return {};
	}

	if (Json::parseFromStream(builder, file, &root, &errs))
	{
		for (const auto& key : root.getMemberNames())
		{
			Enemy* obj = new Enemy({
				CreateRigidBodyComponent(root[key]),
				CreateCollisionComponent(root[key]),
				CreateRenderComponent(root[key]),
				CreateAIComponent(root[key])
				});

			m_AllGameObject[obj->GetId()] = obj;
		}
	}
	else
	{
		std::cerr << "Failed to parse JSON: " << errs << std::endl;
	}

	return m_AllGameObject;
}


std::unordered_map<int, GameObject*> ReadInfo::ReadInfoTerrain()
{
	std::ifstream file("images/TerrainFile.json", std::ios::binary);
	Json::Value root;
	Json::CharReaderBuilder builder;
	std::string errs;

	std::unordered_map<int, GameObject*> m_AllGameObject;

	if (!file.is_open())
	{
		std::cerr << "Could not open TerrainFile.json\n";
		return {};
	}

	if (Json::parseFromStream(builder, file, &root, &errs))
	{
		for (const auto& key : root.getMemberNames())
		{
			Terrain* obj = new Terrain({
				CreateRigidBodyComponent(root[key]),
				CreateCollisionComponent(root[key]),
				CreateRenderComponent(root[key])
				});

			m_AllGameObject[obj->GetId()] = obj;
		}
	}
	else
	{
		std::cerr << "Failed to parse JSON: " << errs << std::endl;
	}

	return m_AllGameObject;
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
	RenderComponent* render = new RenderComponent(data["width"].asFloat(), data["height"].asFloat(),
		Game::getInstance().GetRenderer(), data["image"].asCString());
	return render;
}

AIComponent* ReadInfo::CreateAIComponent(Json::Value& data)
{
	AIComponent* ai = new AIComponent(data["speed"].asInt());
	return ai;
}