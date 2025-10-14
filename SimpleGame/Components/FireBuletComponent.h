#pragma once
#include "Components.h"
#include "RigidBodyComponent.h"
#include "GameObject.h"

class FireBuletComponent:public Components
{
public:

    FireBuletComponent();

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
    void SetBulet(GameObject* bulet) { m_bulet = bulet; }

private:
    const int m_ComponentId = GetUniqueComponentID();
    GameObject* m_bulet;
    float m_deltaTime;

};
