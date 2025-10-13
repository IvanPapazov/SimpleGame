#include "stdafx.h"
#include "ComponentManager.h"
#include <fstream>
#include <GameObject.h>
#include "DrawComponent.h"
#include "GravityComponent.h"
#include "JumpComponent.h"
#include "MoveLeftRightComponent.h"
#include <Components/FireBuletComponent.h>

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
            if (playerKey.find("player") != std::string::npos)
            {
                GameObject* player = CreatePlayerObject(ms_RendererManager, root[playerKey]);
                values.push_back(player);
            }
           /* if (playerKey.find("bulet") != std::string::npos)
            {
                GameObject* bulet = CreateBuletObject(ms_RendererManager, root[playerKey]);
                values.push_back(bulet);
            }*/
            if (playerKey.find("enemy") != std::string::npos)
            {
                GameObject* enemy = CreateEnemyObject(ms_RendererManager, root[playerKey]);
                values.push_back(enemy);
            }
        }
    }
    else {
        std::cerr << "Failed to parse JSON: " << errs << std::endl;
    }

    return values;
}

GameObject* ComponentManager::CreateBuletObject(RenderingManager& ms_RendererManager, Json::Value& playerInfo)
{
    GameObject* bulet = new GameObject();
    RigidBodyComponent* rbComp = new RigidBodyComponent
    (Vec2(0, 0), Vec2(0.0f, 0.0f), Vec2(0.0f, 0.0f));
    DrawComponent* drawComp = new DrawComponent(playerInfo["width"].asFloat(), playerInfo["height"].asFloat(), ms_RendererManager.GetRenderer(), rbComp, playerInfo["image"].asString().c_str());
    bulet->AddComponent(drawComp);

    return bulet;
}

GameObject* ComponentManager::CreatePlayerObject(RenderingManager& ms_RendererManager, Json::Value& playerInfo)
{
	GameObject* player = new GameObject();
	RigidBodyComponent* rbComp = new RigidBodyComponent
	(Vec2(playerInfo["x"].asFloat(), playerInfo["y"].asFloat()), Vec2(0.0f, 0.0f), Vec2(0.0f, 0.0f));
	DrawComponent* drawComp = new DrawComponent(playerInfo["width"].asFloat(), playerInfo["height"].asFloat(), ms_RendererManager.GetRenderer(), rbComp, playerInfo["image"].asString().c_str());
	player->AddComponent(drawComp);
	GravityComponent* gravityComp = new GravityComponent(rbComp, playerInfo["mass"].asFloat(), playerInfo["height"].asFloat());
	player->AddComponent(gravityComp);
	JumpComponent* jumpComp = new JumpComponent(rbComp, playerInfo["height"].asFloat());
	player->AddComponent(jumpComp);
	MoveLeftRightComponent* moveLeftRightComp = new MoveLeftRightComponent(rbComp, playerInfo["mass"].asFloat(),0.0f);
	player->AddComponent(moveLeftRightComp);

	return player;
}

GameObject* ComponentManager::CreateEnemyObject(RenderingManager& ms_RendererManager, Json::Value& playerInfo)
{
    GameObject* enemy = new GameObject();
    RigidBodyComponent* rbEnemyComp = new RigidBodyComponent
    (Vec2(playerInfo["x"].asFloat(), playerInfo["y"].asFloat()), Vec2(0.0f, 0.0f), Vec2(0.0f, 0.0f));
    DrawComponent* drawComp = new DrawComponent(playerInfo["width"].asFloat(), playerInfo["height"].asFloat(), ms_RendererManager.GetRenderer(), rbEnemyComp, playerInfo["image"].asString().c_str());
    enemy->AddComponent(drawComp);
    GravityComponent* gravityComp = new GravityComponent(rbEnemyComp, playerInfo["mass"].asFloat(), playerInfo["height"].asFloat());
    enemy->AddComponent(gravityComp);
    JumpComponent* jumpComp = new JumpComponent(rbEnemyComp, playerInfo["height"].asFloat());
    enemy->AddComponent(jumpComp);
    MoveLeftRightComponent* moveLeftRightComp = new MoveLeftRightComponent(rbEnemyComp, playerInfo["mass"].asFloat(), 0.0f);
    enemy->AddComponent(moveLeftRightComp);
    RigidBodyComponent* rbBuletComp = new RigidBodyComponent
    (Vec2(0, 0), Vec2(0.0f, 0.0f), Vec2(0.0f, 0.0f));
    FireBuletComponent* fireBuletComp = new FireBuletComponent(rbBuletComp, rbEnemyComp);
    enemy->AddComponent(fireBuletComp);

    return enemy;
}

