#pragma once
#include "stdafx.h"
#include <vector>
#include <Core/System.h>
#include <unordered_map>

class SystemManager : public System{
public:
    void UpdateAll() {
      /*  for (auto& [key,system]: m_Systems) {
            system->Update();
        }*/
    }
};