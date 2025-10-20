#pragma once
#include "stdafx.h"
class MovementComponent : public System
{
private:
	float m_GravityScale = 9.8f;
	float m_Mass, m_DeltaTime;
public:
	MovementComponent(float mass, float deltaTime)
		: m_Mass(mass), m_DeltaTime(deltaTime) {};

	void Update();
};
