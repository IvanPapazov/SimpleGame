#include "stdafx.h"
#include "Terrain.h"
#include "iostream"

void Terrain::UpdateComponents(GameObject* obj, std::unordered_map<int, GameObject*> gameObjects)
{
	for (auto& [type, comp] : m_Components) {
		comp->Update(obj, gameObjects);
	}
}