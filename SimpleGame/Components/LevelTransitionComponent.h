#pragma once
#include "stdafx.h"
#include <SDL.h>
#include <Core/Component.h>
#include <Utils/Vec2.h>
#include <Utils/Timer.h>

class LevelTransitionComponent : public Component {
private:
    Timer m_TransitionTimer;
    bool m_TimerStarted = false;

public:
    LevelTransitionComponent();
    ~LevelTransitionComponent() = default;
    void Update();

};
