#pragma once

#include "AudioMixer.g.h"

namespace winrt::FourShot::Audio::implementation
{
    struct AudioMixer : AudioMixerT<AudioMixer>
    {
        AudioMixer() = default;

        void Start(Audio::AudioEndpoint const& sourceEndpoint, Audio::AudioEndpoint const& targetEndpoint);
    };
}

namespace winrt::FourShot::Audio::factory_implementation
{
    struct AudioMixer : AudioMixerT<AudioMixer, implementation::AudioMixer>
    {
    };
}
