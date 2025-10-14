#pragma once
#include "Components.h"
#include "RigidBodyComponent.h"

const float mg_Gravity = 9.8f;
class GravityComponent : public Components
{
public:
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
    GravityComponent(RigidBodyComponent* rb,float m_Mass,float m_Height);
    int GetComponentId() override {
        return m_ComponentId;
    }

    RigidBodyComponent* GetRigidBodyComponent() const {
        return m_RigidBodyComponent;
    }
    void HandleAllEvents() override;
    void Update() override;
private:
    RigidBodyComponent* m_RigidBodyComponent;
    const int m_ComponentId = GetUniqueComponentID();
    Uint64 m_Last = SDL_GetPerformanceCounter();

    float m_Height;
    float m_Mass;
    float m_deltaTime;
};
