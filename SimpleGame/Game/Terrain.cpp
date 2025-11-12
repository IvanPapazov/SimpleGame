#include "stdafx.h"
#include "Terrain.h"
#include <iostream>

void Terrain::UpdateComponents()
{
    for (auto& [type, comp] : m_Components) {
        if (comp) {
            comp->Update();
        }
    }
}
