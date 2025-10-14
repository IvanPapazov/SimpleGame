#pragma once
#include <RenderingManager.h>
#include <any>


class GameObjectFactory
{
private:
	GameObject* CreatePlayerObject(RenderingManager& ms_RendererManager, Json::Value& player);
	GameObject* CreateBulletObject(RenderingManager& ms_RendererManager, Json::Value& player);
	GameObject* CreateEnemyObject(RenderingManager& ms_RendererManager, Json::Value& player);
    
public:
    GameObjectFactory();
	std::vector<GameObject*> ReadInfo(RenderingManager& ms_RendererManager);
};

