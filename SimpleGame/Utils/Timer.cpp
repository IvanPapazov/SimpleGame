#include "stdafx.h"
#include "Timer.h"

Timer::Timer()
	: m_StartTime(0), m_Duration(0), m_Running(false), m_Callback(nullptr) {}


void Timer::Update(Uint32 durationMs, Callback callback) {
    Uint32 now = SDL_GetTicks();

    if (!m_Running) {
        m_StartTime = now;
        m_Duration = durationMs;
        m_Callback = callback;
        m_Running = true;
        return;
    }

    if (now - m_StartTime >= m_Duration) {
        if (m_Callback) m_Callback();
        Stop();
    }
}

void Timer::Stop() {
	m_Running = false;
	m_Callback = nullptr;
}

bool Timer::IsRunning() const {
	return m_Running;
}
