#include "stdafx.h"
#include "GameObjectFactory.h"
#include <fstream>
#include <GameObject.h>
#include "Components/RigidBodyComponent.h"
#include "Components/DrawComponent.h"
#include "Components/GravityComponent.h"
#include "Components/JumpComponent.h"
#include "Components/MoveLeftRightComponent.h"
#include <Components/FireBulletComponent.h>

GameObjectFactory::GameObjectFactory() {}

std::unordered_map<std::string, Components*> GameObjectFactory::ReadInfo(RenderingManager& rendererManager)
{
    std::ifstream file("images/PlayerFile.json", std::ios::binary);
    Json::Value root;
    Json::CharReaderBuilder builder;
    std::string errs;

    std::unordered_map<std::string, Components*> m_AllComponents;
     
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
            auto* rb = CreateRigidBodyComponent(root[key]);
            if (key.find("player") != std::string::npos) 
            {
                
                m_AllComponents["DrawPlayer"] = CreateDrawComponent(rendererManager, rb, root[key]);
                m_AllComponents["GravityPlayer"] = CreateGraviryComponent(rb, root[key]);
                m_AllComponents["MovePlayer"] = CreateMoveComponent(rb, root[key]);
                m_AllComponents["JumpPlayer"] = CreateJumpComponent(rb, root[key]);
            }
            else if (key.find("bullet") != std::string::npos) 
            {
                m_AllComponents["DrawBullet"] = CreateDrawComponent(rendererManager, rb, root[key]);
                m_AllComponents["FireBulletEnemy"] = CreateFireBuletComponent(rb);

            }
            else if (key.find("enemy") != std::string::npos) 
            {
                
                m_AllComponents["DrawEnemy"] = CreateDrawComponent(rendererManager, rb, root[key]);
                m_AllComponents["GravityEnemy"] = CreateGraviryComponent(rb, root[key]);
                m_AllComponents["MoveEnemy"] = CreateMoveComponent(rb, root[key]);
                m_AllComponents["JumpEnemy"] = CreateJumpComponent(rb, root[key]);
            }
        }
    }
    else 
    {
        std::cerr << "Failed to parse JSON: " << errs << std::endl;
    }

    return m_AllComponents;
}

RigidBodyComponent* GameObjectFactory::CreateRigidBodyComponent(Json::Value& data)
{
    RigidBodyComponent* rb = new RigidBodyComponent(Vec2(data["x"].asFloat(), data["y"].asFloat()),
        Vec2(0.0f, 0.0f), Vec2(0.0f, 0.0f));
    return rb;
}

Components* GameObjectFactory::CreateDrawComponent(RenderingManager& rendererManager, RigidBodyComponent* rb, Json::Value& data)
{
    Components* draw = new DrawComponent(data["width"].asFloat(), data["height"].asFloat(),
        rendererManager.GetRenderer(), rb, data["image"].asCString());
    return draw;
}

Components* GameObjectFactory::CreateGraviryComponent(RigidBodyComponent* rb, Json::Value& data)
{
    Components* gravity = new GravityComponent(rb, data["mass"].asFloat(), data["height"].asFloat());
    return gravity;
}

Components* GameObjectFactory::CreateJumpComponent(RigidBodyComponent* rb, Json::Value& data)
{
    Components* jump = new JumpComponent(rb, data["height"].asFloat());
    return jump;
}

Components* GameObjectFactory::CreateMoveComponent(RigidBodyComponent* rb, Json::Value& data)
{
    Components* move = new MoveLeftRightComponent(rb, data["mass"].asFloat());
    return move;
}

Components* GameObjectFactory::CreateFireBuletComponent(RigidBodyComponent* rb)
{
    Components* fire = new FireBulletComponent(rb);
    return fire;
}
