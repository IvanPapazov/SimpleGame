#pragma once

class HealthComponent
{
private:
	bool m_IsActive = true;
	int m_Health;
public:
	HealthComponent(int health)
		:m_Health(health){}
};
