#pragma once

#include "AudioEndpoint.g.h"

namespace winrt::FourShot::Audio::implementation
{
    struct AudioEndpoint : AudioEndpointT<AudioEndpoint>
    {
        AudioEndpoint(wil::com_ptr<IMMDevice>&& spDefaultAudioEndpoint);

        hstring Name() const;

        void StartLoopbackCapture();
        void StartRendering();

    private:
        wil::com_ptr<IMMDevice> m_spAudioEndpoint;
        hstring m_name;
    };
}
