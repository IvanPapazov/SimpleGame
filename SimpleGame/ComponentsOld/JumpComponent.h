#pragma once
#include "Components.h"
#include "RigidBodyComponent.h"

class JumpComponent : public Components
{
public:
    void HandleAllEvents() override;
    void Update() override;
    JumpComponent(RigidBodyComponent* rb,float m_Height);
    JumpComponent* Clone() const override {
        return new JumpComponent(*this);;
    }
    int GetComponentId() override {
        return m_ComponentId;
    }
    float GetHeight() const {
        return m_Height;
    }

    void SetHeight(float height) {
        m_Height = height;
    }

    void SetRigidBodyComponent(RigidBodyComponent* rigidBodyComponent) {
        m_RigidBodyComponent = rigidBodyComponent;
    }

private:
    RigidBodyComponent* m_RigidBodyComponent;
    const int m_ComponentId = GetUniqueComponentID();

    float m_Height;
};
