#pragma once
#include "Components.h"
#include "RigidBodyComponent.h"

class MoveLeftComponent : public Components
{
public:

    MoveLeftComponent(RigidBodyComponent* rb, float m_Mass);
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

private:
    RigidBodyComponent* m_RigidBodyComponent;
    const int m_ComponentId = GetUniqueComponentID();

    float m_Mass;
    float GetMass() const { return m_Mass; }

};
