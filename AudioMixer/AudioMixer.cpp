#include "pch.h"
#include "AudioMixer.h"
#include "AudioEndpoint.h"
#if __has_include("AudioMixer.g.cpp")
#include "AudioMixer.g.cpp"
#endif

namespace winrt::FourShot::Audio::implementation
{
    void AudioMixer::Start(Audio::AudioEndpoint const& sourceEndpoint, Audio::AudioEndpoint const& targetEndpoint)
    {
        get_self<AudioEndpoint>(sourceEndpoint)->StartLoopbackCapture();
        get_self<AudioEndpoint>(targetEndpoint)->StartRendering();
    }
}
