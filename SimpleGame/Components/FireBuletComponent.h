#pragma once
#include "Components.h"
#include "RigidBodyComponent.h"
#include "GameObject.h"

class FireBuletComponent:public Components
{
public:

    FireBuletComponent();

    int GetComponentId() override {
        return m_ComponentId;
    }

    void Update() override; 
    void HandleAllEvents() override;
    void SetBullet(GameObject* bullet) { m_bulet = bullet; }

private:
    const int m_ComponentId = GetUniqueComponentID();
    GameObject* m_bulet;
    Uint64 m_Last = SDL_GetPerformanceCounter();
    float m_deltaTime;

};
