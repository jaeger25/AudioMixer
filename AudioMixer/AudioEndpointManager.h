#pragma once

#include "AudioEndpointManager.g.h"

namespace winrt::FourShot::Audio::implementation
{
    struct AudioEndpointManager : AudioEndpointManagerT<AudioEndpointManager>
    {
        AudioEndpointManager();

        IVectorView<Audio::AudioEndpoint> Endpoints() const;

    private:
        IVector<Audio::AudioEndpoint> m_audioEndpoints;
    };
}

namespace winrt::FourShot::Audio::factory_implementation
{
    struct AudioEndpointManager : AudioEndpointManagerT<AudioEndpointManager, implementation::AudioEndpointManager>
    {
    };
}
