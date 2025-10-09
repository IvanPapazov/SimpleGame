#pragma once
#include "Components.h"
#include "RigidBodyComponent.h"

class JumpComponent : public Components
{
public:

    JumpComponent(RigidBodyComponent* rb, float m_Mass);
    int GetComponentId() override {
        return m_ComponentId;
    }

private:
    RigidBodyComponent* m_RigidBodyComponent;
    const int m_ComponentId = GetUniqueComponentID();

    float m_Mass;
    float GetMass() const { return m_Mass; }

    void Update() override;
};
