#include "stdafx.h"
#include "Heart.h"
#include "iostream"

void Heart::UpdateComponents(GameObject* obj)
{
	for (auto& [type, comp] : m_Components) {
		comp->Update(obj);
	}
}