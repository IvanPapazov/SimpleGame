#include "stdafx.h"
#include "Timer.h"

void Timer::Start() {
    m_Running = true;
    m_Paused = false;
    m_StartTime = SDL_GetTicks();
    m_PausedTime = 0;
}

void Timer::Stop() {
    m_Running = false;
    m_Paused = false;
    m_StartTime = 0;
    m_PausedTime = 0;
}

void Timer::Pause() {
    if (m_Running && !m_Paused) {
        m_Paused = true;
        m_PausedTime = SDL_GetTicks() - m_StartTime;
    }
}

void Timer::Resume() {
    if (m_Running && m_Paused) {
        m_Paused = false;
        m_StartTime = SDL_GetTicks() - m_PausedTime;
        m_PausedTime = 0;
    }
}

Uint32 Timer::GetElapsed() const {
    if (!m_Running) return 0;
    if (m_Paused) return m_PausedTime;
    return SDL_GetTicks() - m_StartTime;
}
