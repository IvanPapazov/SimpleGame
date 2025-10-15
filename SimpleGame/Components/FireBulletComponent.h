#pragma once
#include "Components.h"
#include "RigidBodyComponent.h"
#include "GameObject.h"

class FireBulletComponent:public Components
{
public:

    FireBulletComponent(RigidBodyComponent* rb);
    FireBulletComponent* Clone() const override {
        return new FireBulletComponent(*this);
    }

    int GetComponentId() override {
        return m_ComponentId;
    }

    RigidBodyComponent* GetRigidBodyComponent() const {
        return m_RigidBodyComponent;
    }
    void SetRigidBodyComponent(RigidBodyComponent* rigidBodyComponent) {
        m_RigidBodyComponent = rigidBodyComponent;
    }

    void Update() override;
    void HandleAllEvents() override;

private:
    RigidBodyComponent* m_RigidBodyComponent;
    const int m_ComponentId = GetUniqueComponentID();
    Uint64 m_Last = SDL_GetPerformanceCounter();
    float m_deltaTime;

};
