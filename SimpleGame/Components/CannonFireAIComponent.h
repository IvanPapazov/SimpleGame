#pragma once
#include <Components/AIComponent.h>
#include <Utils/Timer.h>
#include <memory>
#include <vector>

class CannonFireAIComponent : public AIComponent
{
private:
    Timer m_TransitionTimer;
    std::vector<std::unique_ptr<GameObject>> m_Amo;

public:
    explicit CannonFireAIComponent(float speed);
    ~CannonFireAIComponent() override = default;

    void Update() override;
};
