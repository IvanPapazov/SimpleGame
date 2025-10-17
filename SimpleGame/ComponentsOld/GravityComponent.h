#pragma once
#include "Components.h"
#include "RigidBodyComponent.h"

const float mg_Gravity = 9.8f;
class GravityComponent : public Components
{
public:
    GravityComponent(RigidBodyComponent* rb, float m_Mass, float m_Height);
    GravityComponent* Clone() const override {
        return new GravityComponent(*this);
    }

    float GetHeight() const {
        return m_Height;
    }
    void SetHeight(float height) {
        m_Height = height;
    }
    float GetMass() const {
        return m_Mass;
    }
    void SetMass(float mass) {
        m_Mass = mass;
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
private:
    RigidBodyComponent* m_RigidBodyComponent;
    const int m_ComponentId = GetUniqueComponentID();
    Uint64 m_Last = SDL_GetPerformanceCounter();

    float m_Height;
    float m_Mass;
    float m_deltaTime;
};
