#include "AudioSource.h"

namespace Orca 
{
    void AudioSource::SetStream(std::shared_ptr<AudioStream> stream) 
    {
        m_Stream = stream;
    }

    void AudioSource::Play() 
    {
        if (m_Stream) m_Stream->Play();
    }

    void AudioSource::Stop() 
    {
        if (m_Stream) m_Stream->Stop();
    }
}