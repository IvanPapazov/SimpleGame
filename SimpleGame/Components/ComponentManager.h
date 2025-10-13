#pragma once
#include <RenderingManager.h>
#include <any>


class ComponentManager
{
private:
	GameObject* CreatePlayerObject(RenderingManager& ms_RendererManager, Json::Value& player);
	GameObject* CreateBuletObject(RenderingManager& ms_RendererManager, Json::Value& player);
	GameObject* CreateEnemyObject(RenderingManager& ms_RendererManager, Json::Value& player);
    
public:
    ComponentManager();
	std::vector<GameObject*> ReadInfo(RenderingManager& ms_RendererManager);
};

