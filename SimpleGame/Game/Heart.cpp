#include "stdafx.h"
#include "Heart.h"
#include "iostream"

void Heart::UpdateComponents()
{
    for (auto& [type, comp] : m_Components) {
        if (comp) {
            comp->Update();
        }
    }
}