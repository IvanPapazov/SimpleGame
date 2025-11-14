#pragma once
#include <Components/AIComponent.h>

class EnemyRunAIComponent : public AIComponent
{
public:
	~EnemyRunAIComponent() = default;
	EnemyRunAIComponent(float speed);
	void Update();
};