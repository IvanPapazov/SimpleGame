#pragma once
#include <Components/AIComponent.h>
#include <Utils/Timer.h>
#include <memory>
#include <vector>
#include <Game/EnemyCannonBall.h>

class CannonFireAIComponent : public AIComponent
{
private:
    Timer m_TransitionTimer;
    std::vector<EnemyCannonBall*> m_CannonBalls;
    bool m_Fire = false;
public:
    explicit CannonFireAIComponent(float speed);
    ~CannonFireAIComponent() override = default;

    void Update() override;

    void AddCannonBall(EnemyCannonBall* cannonBall) {
        m_CannonBalls.push_back(cannonBall);
    }
};
