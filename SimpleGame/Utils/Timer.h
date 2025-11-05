#pragma once
#include <SDL.h>

class Timer {
private:
    Uint32 m_StartTime = 0;
    Uint32 m_PausedTime = 0;
    bool m_Running = false;
    bool m_Paused = false;

public:
    Timer() = default;

    void Start();
    void Stop();
    void Pause();
    void Resume();

    Uint32 GetElapsed() const;
    bool IsRunning() const { return m_Running; }
    bool IsPaused() const { return m_Paused; }
};
