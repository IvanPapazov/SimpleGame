#pragma once
#include "Components.h"
#include "RigidBodyComponent.h"

const float mg_Gravity = 9.8f;
class GravityComponent : public Components
{
public:
    GravityComponent(RigidBodyComponent* rb,float m_Mass);
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
