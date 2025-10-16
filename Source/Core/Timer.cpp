#include "Timer.h"

namespace Orca 
{
    Timer::Timer() 
    {
        Reset();
    }

    void Timer::Reset() 
    {
        start = std::chrono::steady_clock::now();
        time = 0.0f;
    }

    void Timer::Update() 
    {
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<float> elapsed = now - start;
        time = elapsed.count();
    }

    float Timer::GetElapsedSeconds() const 
    {
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<float> elapsed = now - start;
        return elapsed.count();
    }

    float Timer::GetTime() const 
    {
        return time;
    }
}