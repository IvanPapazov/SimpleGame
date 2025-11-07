#pragma once
#include "stdafx.h"
#include <unordered_map>
#include <Game/GameObject.h>

class AIComponent : public Component
{
protected:
	float m_Speed;
public:
	~AIComponent() = default;
	AIComponent(float speed) :m_Speed(speed) {}
	void Update()=0;
	float GetSpeed() const { return m_Speed; };
};
