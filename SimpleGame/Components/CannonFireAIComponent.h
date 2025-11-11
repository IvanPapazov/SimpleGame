#pragma once
#include <Components/AIComponent.h>
#include <Utils/Timer.h>

class CannonFireAIComponent : public AIComponent
{
private:
	Timer m_TransitionTimer;
	std::vector<GameObject*> m_Amo;
public:
	~CannonFireAIComponent() = default;
	CannonFireAIComponent(float speed);
	void Update();
};

