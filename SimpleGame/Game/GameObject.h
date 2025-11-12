#pragma once
#include "stdafx.h"
#include <unordered_map>
#include <memory>
#include <typeindex>
#include <vector>
#include "Core/Component.h"

class Component;

class GameObject
{
protected:
    int m_Id;
    bool m_IsActive = true;

   
    std::unordered_map<std::type_index, std::unique_ptr<Component>> m_Components;

public:
    GameObject(std::vector<std::unique_ptr<Component>> comps);
    virtual ~GameObject();

    virtual void UpdateComponents() = 0;

    int GetId() const;

    void ClearComponents();
    void AddComponent(std::unique_ptr<Component> component);

    template<typename T>
    T* GetComponent() {
        auto it = m_Components.find(typeid(T));
        if (it != m_Components.end()) {
            return dynamic_cast<T*>(it->second.get());
        }
        return nullptr;
    }

    template<typename T>
    bool HasComponent() {
        return GetComponent<T>() != nullptr;
    }

    bool operator==(const GameObject& other) const {
        return m_Id == other.m_Id;
    }

    bool GetIsActive() const { return m_IsActive; }
    void SetIsActive(bool isActive) { m_IsActive = isActive; }
};
