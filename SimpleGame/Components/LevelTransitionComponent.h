#pragma once
#include "stdafx.h"
#include <SDL.h>
#include <Core/Component.h>
#include <Utils/Vec2.h>
#include <Utils/Timer.h>

class LevelTransitionComponent : public Component {
private:
    std::string m_Level;
    Timer m_TransitionTimer;
public:
    LevelTransitionComponent(std::string level);
    ~LevelTransitionComponent() = default;

    const std::string& GetLevel() const { return m_Level; }
    void Update();

};
