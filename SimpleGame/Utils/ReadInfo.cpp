#include "stdafx.h"
#include "ReadInfo.h"
#include <fstream>
#include <iostream>
#include "Game/Player.h"

std::unordered_map<int, GameObject*> ReadInfo::ReadInfoPlayer(Game& ms_Game)
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
				CreateRenderComponent(ms_Game, root[key]) 
				});

			/* if (key.find("player") != std::string::npos)
			 {*/
			 /* obj->AddComponent(CreateDrawComponent(rendererManager, rb, root[key]));
			  obj->AddComponent(CreateGraviryComponent(rb, root[key]));
			  obj->AddComponent(CreateMoveComponent(rb, root[key]));
			  obj->AddComponent(CreateJumpComponent(rb, root[key]));*/
			  // }
			
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
RenderComponent* ReadInfo::CreateRenderComponent(Game& game, Json::Value& data)
{
	RenderComponent* render = new RenderComponent(data["width"].asFloat(), data["height"].asFloat(),
		game.GetRenderer(), data["image"].asCString());
	return render;
}