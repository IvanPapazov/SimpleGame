#pragma once
#include <RenderingManager.h>
#include <any>
#include "Components/RigidBodyComponent.h"
#include "Components/DrawComponent.h"
#include "Components/GravityComponent.h"
#include "Components/JumpComponent.h"
#include "Components/MoveLeftRightComponent.h"
#include "Components/FireBulletComponent.h"


class GameObjectFactory
{
private:

	RigidBodyComponent* CreateRigidBodyComponent(Json::Value& player);
	Components* CreateDrawComponent(RenderingManager& ms_RendererManager, RigidBodyComponent* rb, Json::Value& player);
	Components* CreateGraviryComponent(RigidBodyComponent* rb, Json::Value& player);
	Components* CreateJumpComponent(RigidBodyComponent* rb, Json::Value& player);
	Components* CreateMoveComponent(RigidBodyComponent* rb, Json::Value& player);
	Components* CreateFireBuletComponent(RigidBodyComponent* rb);
public:
    GameObjectFactory();
	std::unordered_map<std::string, Components*> ReadInfo(RenderingManager& ms_RendererManager);
};

