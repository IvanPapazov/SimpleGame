#include "ComponentManager.h"
#include <GameObject.h>
#include "DrawComponent.h"
#include "GravityComponent.h"
#include "JumpComponent.h"
#include "MoveComponent.h"

GameObject* player = new GameObject();
RigidBodyComponent* rbComp = new RigidBodyComponent(Vec2(100.0f, 100.0f), Vec2(0.0f, 0.0f), Vec2(0.0f, 0.0f));
ComponentManager::ComponentManager() {}

GameObject* ComponentManager::CreateGameObject(RenderingManager& ms_RendererManager)
{
	SetLast(GetNow());
	SetNow(SDL_GetPerformanceCounter());
	float deltaTime = (float)((m_Now - m_Last) * 1000.0f / (float)SDL_GetPerformanceFrequency()) / 1000.0f;
	
	GameObject* player = new GameObject();
	RigidBodyComponent* rbComp = new RigidBodyComponent(Vec2(100.0f, 100.0f), Vec2(0.0f, 0.0f), Vec2(0.0f, 0.0f));
	DrawComponent* drawComp = new DrawComponent(80.0f, 100.0f, ms_RendererManager.GetRenderer(), rbComp, "images/preview.png");
	player->AddComponent(drawComp);
	GravityComponent* gravityComp = new GravityComponent(rbComp, 7.0f);
	player->AddComponent(gravityComp);
	JumpComponent* jumpComp = new JumpComponent(rbComp, 7.0f);
	player->AddComponent(jumpComp);
	MoveComponent* moveComp = new MoveComponent(rbComp, 7.0f);
	player->AddComponent(moveComp);

	return player;
}

