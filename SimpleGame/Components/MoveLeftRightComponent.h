#pragma once
#include "Components.h"
#include "RigidBodyComponent.h"

class MoveLeftRightComponent : public Components
{
public:

    MoveLeftRightComponent(RigidBodyComponent* rb, float m_Mass, float deltaTime);
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
    float GetMass() const { return m_Mass; }
    void SetMass(float mass) { m_Mass = mass; }
    float GetDeltaTime() const { return m_deltaTime; }
    void SetDeltaTime(float deltaTime) { m_deltaTime = deltaTime; }

private:
    RigidBodyComponent* m_RigidBodyComponent;
    const int m_ComponentId = GetUniqueComponentID();

    float m_Mass;
    float m_deltaTime;

};
