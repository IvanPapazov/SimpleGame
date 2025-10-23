#include "stdafx.h"
#include "Terrain.h"
#include "iostream"

void Terrain::UpdateComponents(GameObject* obj)
{
	for (auto& [type, comp] : m_Components) {
		comp->Update(obj);
	}
}