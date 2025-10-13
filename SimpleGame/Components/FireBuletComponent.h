#pragma once
#include "Components.h"
#include "RigidBodyComponent.h"

class FireBuletComponent:public Components
{
public:

    FireBuletComponent(RigidBodyComponent* rb_bulet, RigidBodyComponent* rb_enemy);

    int GetComponentId() override {
        return m_ComponentId;
    }

    /*RigidBodyComponent* GetRigidBodyBulet() const {
        return m_RigidBodyBulet;
    }

    void SetRigidBodyBulet(RigidBodyComponent* rb_bulet) {
        m_RigidBodyBulet = rb_bulet;
    }

    RigidBodyComponent* GetRigidBodyEnemy() const {
        return m_RigidBodyEnemy;
    }

    void SetRigidBodyEnemy(RigidBodyComponent* rb_enemy) {
        m_RigidBodyEnemy = rb_enemy;
    }*/

    void Update() override; 

    float GetDeltaTime() const { return m_deltaTime; }
    void SetDeltaTime(float deltaTime) { m_deltaTime = deltaTime; }

private:
    const int m_ComponentId = GetUniqueComponentID();
    RigidBodyComponent* m_RigidBodyBulet;
    RigidBodyComponent* m_RigidBodyEnemy;
    float m_deltaTime;

};
