#pragma once
#include "stdafx.h"
#include <SDL.h>
#include <Core/Component.h>
#include <Utils/Vec2.h>
#include <Utils/Timer.h>

class LevelTransitionComponent : public Component {
private:
    std::string m_NextLevel;
    std::string m_PreviousLevel;
    Timer m_TransitionTimer;
public:
    LevelTransitionComponent(std::string nextLevel, std::string previousLevel);
    ~LevelTransitionComponent() = default;

    const std::string& GetLevel() const {
        return !m_NextLevel.empty() ? m_NextLevel : m_PreviousLevel;
    }
    const std::string& getNextLevel() const { return m_NextLevel; }
    const std::string& getPreviousLevel() const { return m_PreviousLevel; }
    void Update();

};
