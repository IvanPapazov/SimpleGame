#include "stdafx.h"
#include "GameObjectManager.h"
#include <Components/GravityComponent.h>
#include <Components/DrawComponent.h>
#include <Components/MoveLeftRightComponent.h>
#include <Components/JumpComponent.h>
#include <Components/FireBulletComponent.h>

GameObjectManager::GameObjectManager() {};

void GameObjectManager::AddGameObject(GameObject* obj) {
	m_gameObjects[obj->GetId()] = obj;
}

void GameObjectManager::CreateGameObject(std::unordered_map<std::string, Components*> components) {
	auto spawnPrefab = [&](const std::string& name) {
		GameObject* gameObject = new GameObject();

		DrawComponent* drawComp = static_cast<DrawComponent*>(components["Draw" + name]);
		RigidBodyComponent* originalRB = drawComp->GetRigidBodyComponent();
		RigidBodyComponent* rbCopy = new RigidBodyComponent(*originalRB);

		DrawComponent* draw = static_cast<DrawComponent*>(components["Draw" + name]->Clone());
		draw->SetRigidBodyComponent(rbCopy);
		gameObject->AddComponent(draw);

		GravityComponent* gravity = static_cast<GravityComponent*>(components["Gravity" + name]->Clone());
		gravity->SetRigidBodyComponent(rbCopy);
		gameObject->AddComponent(gravity);

		MoveLeftRightComponent* move = static_cast<MoveLeftRightComponent*>(components["Move" + name]->Clone());
		move->SetRigidBodyComponent(rbCopy);
		gameObject->AddComponent(move);

		JumpComponent* jump = static_cast<JumpComponent*>(components["Jump" + name]->Clone());
		jump->SetRigidBodyComponent(rbCopy);
		gameObject->AddComponent(jump);
		AddGameObject(gameObject);
	};

	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_E]) 
	{
		spawnPrefab("Player");
	}
	else if (state[SDL_SCANCODE_Q]) {
		spawnPrefab("Enemy");
	}
	else if (state[SDL_SCANCODE_SPACE]) {
		GameObject* gameObject = new GameObject();
		FireBulletComponent* fireBullet = static_cast<FireBulletComponent*>(components["FireBulletEnemy"]->Clone());

		RigidBodyComponent* rbCurrentObject = m_GameObject->GetComponent<DrawComponent>()->GetRigidBodyComponent();

		Vec2 pos = rbCurrentObject->GetPosition() + Vec2(m_GameObject->GetComponent<DrawComponent>()->GetWidth(),m_GameObject->GetComponent<DrawComponent>()->GetHeight()/2) ;
		rbCurrentObject->SetPosition(pos);

		DrawComponent* draw = static_cast<DrawComponent*>(components["DrawBullet"]->Clone());
		draw->SetRigidBodyComponent(rbCurrentObject);
		gameObject->AddComponent(draw);

		fireBullet->SetRigidBodyComponent(rbCurrentObject);
		m_GameObject->AddComponent(fireBullet);
		AddGameObject(gameObject);
	}
}

GameObject* GameObjectManager::GetGameObject(int id) {
	auto it = m_gameObjects.find(id);
	return (it != m_gameObjects.end()) ? it->second : nullptr;
}

void GameObjectManager::RemoveGameObject(int id) {
	auto it = m_gameObjects.find(id);
	if (it != m_gameObjects.end()) {
		delete it->second;
		m_gameObjects.erase(it);
	}
}

void GameObjectManager::UpdateComponents()
{
	for (auto& [id, obj] : m_gameObjects) {
		obj->UpdateComponents();
	}
	if (m_GameObject!=nullptr)
	{
		m_GameObject->HandleAllEvents();
	}
}
void GameObjectManager::HandleAllEvents(float mouseX, float mouseY)
{
	SelectGameObjectAt(mouseX, mouseY, m_gameObjects);
}

const std::unordered_map<int, GameObject*>& GameObjectManager::GetAll() const {
	return m_gameObjects;
}

void GameObjectManager::SelectGameObjectAt(float mouseX, float mouseY, std::unordered_map<int, GameObject*> gameObjects)
{
	for (auto& element : gameObjects)
	{
		if (element.second->HasComponent<GravityComponent>())
		{
			SDL_Rect bounds;
			bounds.x = element.second->GetComponent<GravityComponent>()->GetRigidBodyComponent()->GetPosition().x;
			bounds.y = element.second->GetComponent<GravityComponent>()->GetRigidBodyComponent()->GetPosition().y;
			bounds.w = element.second->GetComponent<DrawComponent>()->GetWidth();
			bounds.h = element.second->GetComponent<DrawComponent>()->GetHeight();

			SDL_Point mousePoint = { mouseX, mouseY };
			if (SDL_PointInRect(&mousePoint, &bounds))
			{
				m_GameObject = element.second;
			}
		}
	}
}
