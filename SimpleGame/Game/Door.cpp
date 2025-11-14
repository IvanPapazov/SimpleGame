#include "stdafx.h"
#include "Door.h"

void Door::UpdateComponents()
{
    for (auto& [type, comp] : m_Components) {
        if (comp) {
            comp->Update();
        }
    }
}