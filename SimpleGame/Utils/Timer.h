#pragma once
#include "stdafx.h"
#include <SDL.h>
#include <functional>

class Timer {
public:
    enum class Mode {
        OneShot,   
        Continuous  
    };

    using Callback = std::function<void()>;

    Timer();

    void Update(Uint32 durationMs, Callback callback, Mode mode = Mode::OneShot);
    void Stop();
    bool IsRunning() const;

private:
    Uint32 m_StartTime;
    Uint32 m_Duration;
    bool m_Running;
    Mode m_Mode;
    Callback m_Callback;
};
