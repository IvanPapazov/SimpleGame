#pragma once
#include "stdafx.h"
#include <vector>
#include <Core/System.h>

class SystemManager {
public:
    void UpdateAll() {
        for (System* system : systems) {
            system->Update();
        }
    }
private:
	std::vector<System*> systems;
};