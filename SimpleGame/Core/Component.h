#pragma once

#include "stdafx.h"
#include <vector>
#include "../Game/GameObject.h"
#include "../Core/GameObjectManager.h"

class GameObject;
class Component {
protected:
    GameObject* m_Owner = nullptr;

public:
    virtual ~Component() = default;
    virtual void Update() {}

    void SetOwner(GameObject* owner) { m_Owner = owner; }
    GameObject* GetOwner() const { return m_Owner; }
};