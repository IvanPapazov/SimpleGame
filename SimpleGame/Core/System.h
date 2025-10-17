#pragma once
#include <vector>
#include <Game/GameObject.h>

class System {
public:
	virtual ~System() = default;
	virtual void Update(float deltaTime, class ComponentManager* cm) {}
	//virtual void Render(class ComponentManager& cm, class SDL_Renderer* renderer) {}
	std::vector<GameObject> m_GameObjects;
};