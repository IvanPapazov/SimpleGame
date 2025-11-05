#include "stdafx.h"
#include "Pathways.h"

void Pathways::UpdateComponents()
{
	for (auto& [type, comp] : m_Components) {
		comp->Update();
	}
}