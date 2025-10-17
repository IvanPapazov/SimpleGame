#pragma once
class MovementComponent
{
private:
	float gravityScale = 9.8f;
	float m_Mass, m_DeltaTime;
public:
	MovementComponent(float mass, float deltaTime)
		: m_Mass(mass), m_DeltaTime(deltaTime) {};
};
