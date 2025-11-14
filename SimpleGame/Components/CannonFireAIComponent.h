#pragma once
#include <Components/AIComponent.h>
#include <Utils/Timer.h>
#include <memory>
#include <vector>

class CannonFireAIComponent : public AIComponent
{
private:
    Timer m_TransitionTimer;

public:
    explicit CannonFireAIComponent(float speed);
    ~CannonFireAIComponent() override = default;

    void Update() override;
};
