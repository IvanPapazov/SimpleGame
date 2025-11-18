#pragma once
#include "stdafx.h"
#include <Utils/Timer.h>
class HealthComponent : public Component
{
private:
	bool m_IsDead = false;
	int m_Health;
	Timer m_TransitionTimer;
public:
	~HealthComponent()= default;
	HealthComponent(int health)
		:m_Health(health){}

	bool IsDead() const {
		return m_IsDead;
	}

	int GetHealth() const { return m_Health; }
	void SetHealth(int health) { m_Health = health; }

	void Update();
};
