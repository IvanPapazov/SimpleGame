#pragma once
#include "stdafx.h"
#include <Utils/Timer.h>
class HealthComponent : public Component
{
private:
	bool m_IsActive = true;
	int m_Health;
	Timer m_TransitionTimer;
public:
	~HealthComponent()= default;
	HealthComponent(int health)
		:m_Health(health){}

	bool IsActive() const {
		return m_IsActive;
	}

	int GetHealth() const { return m_Health; }
	void SetHealth(int health) { m_Health = health; }

	void Update();
};
