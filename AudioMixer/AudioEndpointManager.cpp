#include "pch.h"
#include "AudioEndpointManager.h"
#include "AudioEndpoint.h"
#if __has_include("AudioEndpointManager.g.cpp")
#include "AudioEndpointManager.g.cpp"
#endif

namespace winrt::FourShot::Audio::implementation
{
    AudioEndpointManager::AudioEndpointManager()
    {
        wil::com_ptr<IMMDeviceEnumerator> spDeviceEnumerator;
        THROW_IF_FAILED(CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_ALL, IID_PPV_ARGS(spDeviceEnumerator.put())));

        wil::com_ptr<IMMDeviceCollection> spAudioEndpoints;
        THROW_IF_FAILED(spDeviceEnumerator->EnumAudioEndpoints(eRender, DEVICE_STATE_ACTIVE, spAudioEndpoints.put()));

        UINT audioEndpointCount;
        THROW_IF_FAILED(spAudioEndpoints->GetCount(&audioEndpointCount));

        std::vector<Audio::AudioEndpoint> audioEndpoints;
        audioEndpoints.reserve(audioEndpointCount);
        for (UINT i = 0; i < audioEndpointCount; i++)
        {
            wil::com_ptr<IMMDevice> spAudioDevice;
            THROW_IF_FAILED(spAudioEndpoints->Item(i, spAudioDevice.put()));

            audioEndpoints.push_back(winrt::make<AudioEndpoint>(std::move(spAudioDevice)));
        }

        m_audioEndpoints = single_threaded_vector(std::move(audioEndpoints));
    }

    IVectorView<Audio::AudioEndpoint> AudioEndpointManager::Endpoints() const
    {
        return m_audioEndpoints.GetView();
    }
}
