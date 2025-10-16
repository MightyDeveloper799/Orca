#pragma once

#ifndef AUDIO_SOURCE_H
#define AUDIO_SOURCE_H

#include <memory>
#include "AudioStream.h"

namespace Orca 
{
#pragma warning(push)
#pragma warning(disable: 4251)

    class ORCA_API AudioSource
    {
    public:
        void SetStream(std::shared_ptr<AudioStream> stream);
        void Play();
        void Stop();

    private:
        std::shared_ptr<AudioStream> m_Stream;
    };
#pragma warning(pop)
}

#endif