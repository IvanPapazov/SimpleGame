#pragma once
#include "Components.h"
#include "RigidBodyComponent.h"

class JumpComponent : public Components
{
public:
    void Update() override;
    JumpComponent(RigidBodyComponent* rb,float m_Height);
    int GetComponentId() override {
        return m_ComponentId;
    }
    float GetHeight() const {
        return m_Height;
    }

    void SetHeight(float height) {
        m_Height = height;
    }

private:
    RigidBodyComponent* m_RigidBodyComponent;
    const int m_ComponentId = GetUniqueComponentID();

    float m_Height;
};
