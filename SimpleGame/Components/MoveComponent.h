#pragma once
#include "Components.h"
#include "RigidBodyComponent.h"

class MoveComponent : public Components
{
public:

    MoveComponent(RigidBodyComponent* rb, float m_Mass);
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
