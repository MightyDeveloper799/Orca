#pragma once

#ifndef AUDIO_STREAM_H
#define AUDIO_STREAM_H

#include <string>
#include "OrcaAPI.h"

namespace Orca 
{
#pragma warning(push)
#pragma warning(disable: 4251)

    class ORCA_API AudioStream
    {
    public:
        virtual ~AudioStream() = default;
        virtual bool Load(const std::string& file) = 0;
        virtual void Play() = 0;
        virtual void Stop() = 0;
    };
#pragma warning(pop)
}

#endif