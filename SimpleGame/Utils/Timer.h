#pragma once
#include <SDL.h>
#include <functional>

class Timer {
public:
    using Callback = std::function<void()>;

    Timer();

    void Update(Uint32 durationMs, Callback callback);
    void Stop();
    bool IsRunning() const;

private:
    Uint32 m_StartTime;
    Uint32 m_Duration;
    bool m_Running;
    Callback m_Callback;
};
