#include "stdafx.h"
#include "GameObjectFactory.h"
#include <fstream>
#include <GameObject.h>
#include "Components/DrawComponent.h"
#include "Components/GravityComponent.h"
#include "Components/JumpComponent.h"
#include "Components/MoveLeftRightComponent.h"
#include <Components/FireBuletComponent.h>

GameObjectFactory::GameObjectFactory() {}

std::vector<GameObject*> GameObjectFactory::ReadInfo(RenderingManager& rendererManager) 
{
    std::ifstream file("images/PlayerFile.json", std::ios::binary);
    Json::Value root;
    Json::CharReaderBuilder builder;
    std::string errs;

    std::vector<GameObject*> gameObjects;

    if (!file.is_open()) 
    {
        std::cerr << "Could not open PlayerFile.json\n";
        return {};
    }

    if (Json::parseFromStream(builder, file, &root, &errs)) 
    {
        for (const auto& key : root.getMemberNames()) 
        {
            const Json::Value& data = root[key];

            if (key.find("player") != std::string::npos) 
            {
                gameObjects.push_back(CreatePlayerObject(rendererManager, root[key]));
            }
            else if (key.find("bullet") != std::string::npos) 
            {
                gameObjects.push_back(CreateBulletObject(rendererManager, root[key]));
            }
            else if (key.find("enemy") != std::string::npos) 
            {
                gameObjects.push_back(CreateEnemyObject(rendererManager, root[key]));
            }
        }
    }
    else 
    {
        std::cerr << "Failed to parse JSON: " << errs << std::endl;
    }

    return gameObjects;
}

GameObject* GameObjectFactory::CreateBulletObject(RenderingManager& rendererManager, Json::Value& data) 
{
    GameObject* bullet = new GameObject();

    auto* rb = new RigidBodyComponent(Vec2(-1, -1), Vec2(0.0f, 0.0f), Vec2(0.0f, 0.0f));
    auto* draw = new DrawComponent(data["width"].asFloat(), data["height"].asFloat(),
        rendererManager.GetRenderer(), rb, data["image"].asCString());

    bullet->AddComponent(draw);
    return bullet;
}

GameObject* GameObjectFactory::CreatePlayerObject(RenderingManager& rendererManager, Json::Value& data) 
{
    GameObject* player = new GameObject();

    auto* rb = new RigidBodyComponent(Vec2(data["x"].asFloat(), data["y"].asFloat()),
        Vec2(0.0f, 0.0f), Vec2(0.0f, 0.0f));

    auto* draw = new DrawComponent(data["width"].asFloat(), data["height"].asFloat(),
        rendererManager.GetRenderer(), rb, data["image"].asCString());

    auto* gravity = new GravityComponent(rb, data["mass"].asFloat(), data["height"].asFloat());
    auto* jump = new JumpComponent(rb, data["height"].asFloat());
    auto* move = new MoveLeftRightComponent(rb, data["mass"].asFloat());

    player->AddComponent(draw);
    player->AddComponent(gravity);
    player->AddComponent(jump);
    player->AddComponent(move);

    return player;
}

GameObject* GameObjectFactory::CreateEnemyObject(RenderingManager& rendererManager, Json::Value& data)
{
    GameObject* enemy = new GameObject();

    auto* rb = new RigidBodyComponent(Vec2(data["x"].asFloat(), data["y"].asFloat()),
        Vec2(0.0f, 0.0f), Vec2(0.0f, 0.0f));

    auto* draw = new DrawComponent(data["width"].asFloat(), data["height"].asFloat(),
        rendererManager.GetRenderer(), rb, data["image"].asCString());

    auto* gravity = new GravityComponent(rb, data["mass"].asFloat(), data["height"].asFloat());
    auto* jump = new JumpComponent(rb, data["height"].asFloat());
    auto* move = new MoveLeftRightComponent(rb, data["mass"].asFloat());
    auto* fire = new FireBuletComponent();

    enemy->AddComponent(draw);
    enemy->AddComponent(gravity);
    enemy->AddComponent(jump);
    enemy->AddComponent(move);
    enemy->AddComponent(fire);

    return enemy;
}