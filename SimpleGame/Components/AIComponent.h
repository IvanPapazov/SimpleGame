#pragma once
#include "stdafx.h"
#include <unordered_map>
#include <Game/GameObject.h>

class AIComponent : public Component
{
protected:
	int m_Speed;
public:
	~AIComponent() = default;
	AIComponent(int speed) :m_Speed(speed) {}
	void Update(GameObject* object)=0;
	int GetSpeed() const { return m_Speed; };
};
