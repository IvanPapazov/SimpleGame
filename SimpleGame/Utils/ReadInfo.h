#pragma once
#include <unordered_map>
#include <Game/Game.h>
#include <Game/GameObject.h>
#include <Components/RigidBodyComponent.h>
#include <Components/CollisionComponent.h>
#include <Components/HealthComponent.h>
#include <Components/RenderComponent.h>

class ReadInfo
{
private:

	RigidBodyComponent* CreateRigidBodyComponent(Json::Value& player);
	RenderComponent* CreateRenderComponent(Game& ms_Game, Json::Value& data);
	CollisionComponent* CreateCollisionComponent(Json::Value& player);
	HealthComponent* CreateHealthComponent(Json::Value& player);
	//MoveLeftRightComponent* CreateMoveComponent(RigidBodyComponent* rb, Json::Value& player);
	//FireBulletComponent* CreateFireBuletComponent(RigidBodyComponent* rb);
public:
	//ComponentFactory();
	std::unordered_map<int, GameObject*> ReadInfoPlayer(Game&  ms_Game);
};