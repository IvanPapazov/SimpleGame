#pragma once
#include <Components/AIComponent.h>

class EnemyRunAIComponent : public AIComponent
{
private:
	float m_GravityScale = 9.8f;
public:
	~EnemyRunAIComponent() = default;
	EnemyRunAIComponent(float speed);
	void Update();
};