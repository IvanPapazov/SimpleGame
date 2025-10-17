#pragma once
#include <any>
#include "ComponentsOld/RigidBodyComponent.h"
#include "ComponentsOld/DrawComponent.h"
#include "ComponentsOld/GravityComponent.h"
#include "ComponentsOld/JumpComponent.h"
#include "ComponentsOld/MoveLeftRightComponent.h"
#include "ComponentsOld/FireBulletComponent.h"
#include <systemOld/GameObjectOld.h>


class ComponentFactory
{
private:

	RigidBodyComponent* CreateRigidBodyComponent(Json::Value& player);
	DrawComponent* CreateDrawComponent(RenderingManager& ms_RendererManager, RigidBodyComponent* rb, Json::Value& player);
	GravityComponent* CreateGraviryComponent(RigidBodyComponent* rb, Json::Value& player);
	JumpComponent* CreateJumpComponent(RigidBodyComponent* rb, Json::Value& player);
	MoveLeftRightComponent* CreateMoveComponent(RigidBodyComponent* rb, Json::Value& player);
	FireBulletComponent* CreateFireBuletComponent(RigidBodyComponent* rb);
public:
    ComponentFactory();
	std::unordered_map<int, GameObjectOld*> ReadInfo(RenderingManager& ms_RendererManager);
};

