#pragma once
#include "Components.h"
#include "RigidBodyComponent.h"

class MoveLeftRightComponent : public Components
{
public:

    MoveLeftRightComponent(RigidBodyComponent* rb, float m_Mass);

    int GetComponentId() override {
        return m_ComponentId;
    }

    RigidBodyComponent* GetRigidBodyComponent() const {
        return m_RigidBodyComponent;
    }

    void SetRigidBodyComponent(RigidBodyComponent* rb) {
        m_RigidBodyComponent = rb;
    }

    void Update() override;
    void HandleAllEvents() override;
    float GetMass() const { return m_Mass; }
    void SetMass(float mass) { m_Mass = mass; }

private:
    RigidBodyComponent* m_RigidBodyComponent;
    const int m_ComponentId = GetUniqueComponentID();
    Uint64 m_Last = SDL_GetPerformanceCounter();
    float m_Mass;
    float m_deltaTime;

};
