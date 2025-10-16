#pragma once

#ifndef AUDIO_ENGINE_H
#define AUDIO_ENGINE_H

#include <string>
#include "OrcaAPI.h"

namespace Orca 
{
#pragma warning(push)
#pragma warning(disable: 4251)

    class ORCA_API AudioEngine
    {
    public:
        static void Initialize();
        static void Shutdown();

        static void PlaySound(const std::string& file);
        static void StopAll();
    };
#pragma warning(pop)
}

#endif