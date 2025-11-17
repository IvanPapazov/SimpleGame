#include "stdafx.h"
#include "Timer.h"

Timer::Timer()
    : m_StartTime(0), m_Duration(0), m_Running(false),
    m_Mode(Mode::OneShot), m_Callback(nullptr) {}

void Timer::Update(Uint32 durationMs, Callback callback, Mode mode) {
    Uint32 now = SDL_GetTicks();

    if (!m_Running) {
        m_StartTime = now;
        m_Duration = durationMs;
        m_Callback = callback;
        m_Mode = mode;
        m_Running = true;
        return;
    }

    Uint32 elapsed = now - m_StartTime;

    if (elapsed >= m_Duration) {
        if (m_Mode == Mode::OneShot) {
            if (m_Callback) m_Callback();
            Stop();
        }
        else {
            Stop(); 
        }
    }
    else if (m_Mode == Mode::Continuous) {
        if (m_Callback) m_Callback(); 
    }
}

void Timer::Stop() {
    m_Running = false;
    m_Callback = nullptr;
}

bool Timer::IsRunning() const {
    return m_Running;
}
