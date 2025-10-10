#include "stdafx.h"
#include "ComponentManager.h"
#include <fstream>
#include <GameObject.h>
#include "DrawComponent.h"
#include "GravityComponent.h"
#include "JumpComponent.h"
#include "MoveLeftComponent.h"
#include "MoveRightComponent.h"

ComponentManager::ComponentManager() {}

std::vector<GameObject*> ComponentManager::ReadInfo(RenderingManager& ms_RendererManager)
{
    std::ifstream file("images/PlayerFile.json", std::ios::binary);
    Json::Value root;
    Json::CharReaderBuilder builder;
    std::string errs;

    std::vector<GameObject*> values;
    if (!file.is_open()) {
        std::cerr << "Could not open config.json\n";
        return {};
    }
    if (Json::parseFromStream(builder, file, &root, &errs)) {
        for (const auto& playerKey : root.getMemberNames()) {
            GameObject* player = CreateGameObject(ms_RendererManager, root[playerKey]);
            values.push_back(player);
        }
    }
    else {
        std::cerr << "Failed to parse JSON: " << errs << std::endl;
    }

    return values;
}

GameObject* ComponentManager::CreateGameObject(RenderingManager& ms_RendererManager, Json::Value& playerInfo)
{
	GameObject* player = new GameObject();
	RigidBodyComponent* rbComp = new RigidBodyComponent
	(Vec2(playerInfo["x"].asFloat(), playerInfo["y"].asFloat()), Vec2(0.0f, 0.0f), Vec2(0.0f, 0.0f));
    std::string imagePath = "images/preview.png";
    const char* cPath = imagePath.c_str();
	DrawComponent* drawComp = new DrawComponent(playerInfo["width"].asFloat(), playerInfo["height"].asFloat(), ms_RendererManager.GetRenderer(), rbComp, "images/preview.png");
	player->AddComponent(drawComp);
	GravityComponent* gravityComp = new GravityComponent(rbComp, playerInfo["mass"].asFloat());
	player->AddComponent(gravityComp);
	JumpComponent* jumpComp = new JumpComponent(rbComp, playerInfo["mass"].asFloat());
	player->AddComponent(jumpComp);
	MoveLeftComponent* moveLeftComp = new MoveLeftComponent(rbComp, playerInfo["mass"].asFloat());
	player->AddComponent(moveLeftComp);
	MoveRightComponent* moveRightComp = new MoveRightComponent(rbComp, playerInfo["mass"].asFloat());
	player->AddComponent(moveRightComp);

	return player;
}

