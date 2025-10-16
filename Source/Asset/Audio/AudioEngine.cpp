#include "AudioEngine.h"
#include <include/al.h>
#include <include/alc.h>
#include <iostream>
#include <vector>
#include <fstream>

namespace Orca 
{
    static ALCdevice* s_Device = nullptr;
    static ALCcontext* s_Context = nullptr;

    static std::vector<ALuint> s_Sources;
    static std::vector<ALuint> s_Buffers;

    bool LoadWAV(const std::string& file, std::vector<char>& data, ALenum& format, ALsizei& freq) 
    {
        std::ifstream in(file, std::ios::binary);
        if (!in) 
        {
            std::cerr << "Failed to open WAV file: " << file << std::endl;
            return false;
        }

        in.seekg(44, std::ios::beg);
        data.assign(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());

        format = AL_FORMAT_STEREO16;
        freq = 44100;
        return true;
    }

    void AudioEngine::Initialize() 
    {
        s_Device = alcOpenDevice(nullptr);
        if (!s_Device) 
        {
            std::cerr << "Failed to open OpenAL device!" << std::endl;
            return;
        }

        s_Context = alcCreateContext(s_Device, nullptr);
        if (!s_Context || !alcMakeContextCurrent(s_Context)) 
        {
            std::cerr << "Failed to create OpenAL context!" << std::endl;
            return;
        }
    }

    void AudioEngine::Shutdown() 
    {
        StopAll();

        for (auto buffer : s_Buffers)
            alDeleteBuffers(1, &buffer);
        for (auto source : s_Sources)
            alDeleteSources(1, &source);

        s_Buffers.clear();
        s_Sources.clear();

        alcMakeContextCurrent(nullptr);
        if (s_Context) alcDestroyContext(s_Context);
        if (s_Device) alcCloseDevice(s_Device);
    }

    void AudioEngine::PlaySound(const std::string& file) 
    {
        std::vector<char> audioData;
        ALenum format;
        ALsizei freq;

        if (!LoadWAV(file, audioData, format, freq)) {
            std::cerr << "Failed to load sound: " << file << std::endl;
            return;
        }

        ALuint buffer;
        alGenBuffers(1, &buffer);
        alBufferData(buffer, format, audioData.data(), static_cast<ALsizei>(audioData.size()), freq);
        s_Buffers.push_back(buffer);

        ALuint source;
        alGenSources(1, &source);
        alSourcei(source, AL_BUFFER, buffer);
        alSourcePlay(source);
        s_Sources.push_back(source);
    }

    void AudioEngine::StopAll() 
    {
        for (auto source : s_Sources)
            alSourceStop(source);
    }
}