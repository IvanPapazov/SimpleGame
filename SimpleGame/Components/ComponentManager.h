#pragma once
#include <RenderingManager.h>
#include <any>

struct PlayerData {
	int x;
	int y;
	int width;
	int height;
	int mass;
	std::string image;
};

class ComponentManager
{
private:
	GameObject* CreateGameObject(RenderingManager& ms_RendererManager, Json::Value& player);
    
public:
    ComponentManager();
	std::vector<GameObject*> ReadInfo(RenderingManager& ms_RendererManager);
};

