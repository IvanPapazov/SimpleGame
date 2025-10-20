#include "stdafx.h"
//#include "ComponentFactory.h"
//#include <fstream>
//#include "ComponentsOld/RigidBodyComponent.h"
//#include "ComponentsOld/DrawComponent.h"
//#include "ComponentsOld/GravityComponent.h"
//#include "ComponentsOld/JumpComponent.h"
//#include "ComponentsOld/MoveLeftRightComponent.h"
//#include <ComponentsOld/FireBulletComponent.h>
//#include <systemOld/RenderingManager.h>
//
//ComponentFactory::ComponentFactory() {}
//
//std::unordered_map<int, GameObjectOld*> ComponentFactory::ReadInfo(RenderingManager& rendererManager)
//{
//    std::ifstream file("images/PlayerFile.json", std::ios::binary);
//    Json::Value root;
//    Json::CharReaderBuilder builder;
//    std::string errs;
//
//    std::unordered_map<int, GameObjectOld*> m_AllGameObject;
//
//    if (!file.is_open())
//    {
//        std::cerr << "Could not open PlayerFile.json\n";
//        return {};
//    }
//
//    if (Json::parseFromStream(builder, file, &root, &errs))
//    {
//        for (const auto& key : root.getMemberNames())
//        {
//         /*   auto* rb = CreateRigidBodyComponent(root[key]);
//
//            GameObjectOld* obj = new GameObjectOld();
//
//            if (key.find("player") != std::string::npos)
//            {
//                obj->AddComponent(CreateDrawComponent(rendererManager, rb, root[key]));
//                obj->AddComponent(CreateGraviryComponent(rb, root[key]));
//                obj->AddComponent(CreateMoveComponent(rb, root[key]));
//                obj->AddComponent(CreateJumpComponent(rb, root[key]));
//            }
//            else if (key.find("terrain") != std::string::npos)
//            {
//                obj->AddComponent(CreateDrawComponent(rendererManager, rb, root[key]));
//            }
//            else if (key.find("enemy") != std::string::npos)
//            {
//                obj->AddComponent(CreateDrawComponent(rendererManager, rb, root[key]));
//                obj->AddComponent(CreateGraviryComponent(rb, root[key]));
//            }*/
//
//            m_AllGameObject[obj->GetId()] = obj;
//        }
//    }
//    else
//    {
//        std::cerr << "Failed to parse JSON: " << errs << std::endl;
//    }
//
//    return m_AllGameObject;
//}
//
//RigidBodyComponent* ComponentFactory::CreateRigidBodyComponent(Json::Value& data)
//{
//    RigidBodyComponent* rb = new RigidBodyComponent(Vec2(data["x"].asFloat(), data["y"].asFloat()),
//        Vec2(0.0f, 0.0f), Vec2(0.0f, 0.0f));
//    return rb;
//}
//
//DrawComponent* ComponentFactory::CreateDrawComponent(RenderingManager& rendererManager, RigidBodyComponent* rb, Json::Value& data)
//{
//    DrawComponent* draw = new DrawComponent(data["width"].asFloat(), data["height"].asFloat(),
//        rendererManager.GetRenderer(), rb, data["image"].asCString());
//    return draw;
//}
//
//GravityComponent* ComponentFactory::CreateGraviryComponent(RigidBodyComponent* rb, Json::Value& data)
//{
//    GravityComponent* gravity = new GravityComponent(rb, data["mass"].asFloat(), data["height"].asFloat());
//    return gravity;
//}
//
//JumpComponent* ComponentFactory::CreateJumpComponent(RigidBodyComponent* rb, Json::Value& data)
//{
//    JumpComponent* jump = new JumpComponent(rb, data["height"].asFloat());
//    return jump;
//}
//
//MoveLeftRightComponent* ComponentFactory::CreateMoveComponent(RigidBodyComponent* rb, Json::Value& data)
//{
//    MoveLeftRightComponent* move = new MoveLeftRightComponent(rb, data["mass"].asFloat());
//    return move;
//}
//
//FireBulletComponent* ComponentFactory::CreateFireBuletComponent(RigidBodyComponent* rb)
//{
//    FireBulletComponent* fire = new FireBulletComponent(rb);
//    return fire;
//}