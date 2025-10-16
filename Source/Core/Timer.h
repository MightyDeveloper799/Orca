#pragma once

#ifndef ORCA_TIMER_H
#define ORCA_TIMER_H

#include <chrono>
#include "OrcaAPI.h"

namespace Orca 
{
#pragma warning(push)
#pragma warning(disable: 4251)

    class ORCA_API Timer
    {
    public:
        Timer();

        void Reset();
        void Update();
        float GetElapsedSeconds() const;
        float GetTime() const;

    private:
        std::chrono::steady_clock::time_point start;
        float time = 0.0f;
    };
#pragma warning(pop)
}

#endif