#include "pch.h"
#include "AudioEndpoint.h"
#include "AudioEndpoint.g.cpp"

constexpr REFERENCE_TIME RefTimesPerSecond = 10000000;

namespace winrt::FourShot::Audio::implementation
{
    AudioEndpoint::AudioEndpoint(wil::com_ptr<IMMDevice>&& spAudioEndpoint) :
        m_spAudioEndpoint(std::move(spAudioEndpoint))
    {
        wil::com_ptr<IPropertyStore> spPropertyStore;
        THROW_IF_FAILED(m_spAudioEndpoint->OpenPropertyStore(STGM_READ, spPropertyStore.put()));

        wil::unique_prop_variant spFriendlyName;
        THROW_IF_FAILED(spPropertyStore->GetValue(PKEY_Device_FriendlyName, &spFriendlyName));

        m_name = spFriendlyName.pwszVal;
    }

    hstring AudioEndpoint::Name() const
    {
        return m_name;
    }

    void AudioEndpoint::StartLoopbackCapture()
    {
        wil::com_ptr<IAudioClient> spAudioClient;
        THROW_IF_FAILED(m_spAudioEndpoint->Activate(__uuidof(IAudioClient), CLSCTX_ALL, nullptr, spAudioClient.put_void()));

        wil::unique_cotaskmem_ptr<WAVEFORMATEX> spFormat;
        THROW_IF_FAILED(spAudioClient->GetMixFormat(wil::out_param(spFormat)));

        THROW_IF_FAILED(spAudioClient->Initialize(
            AUDCLNT_SHAREMODE_SHARED,
            AUDCLNT_STREAMFLAGS_LOOPBACK,
            RefTimesPerSecond,
            0,
            spFormat.get(),
            nullptr));

        UINT32 numBufferFrames;
        THROW_IF_FAILED(spAudioClient->GetBufferSize(&numBufferFrames));

        wil::com_ptr<IAudioCaptureClient> spCaptureClient;
        THROW_IF_FAILED(spAudioClient->GetService(__uuidof(IAudioCaptureClient), spCaptureClient.put_void()));
    }

    void AudioEndpoint::StartRendering()
    {
        wil::com_ptr<IAudioClient> spAudioClient;
        THROW_IF_FAILED(m_spAudioEndpoint->Activate(__uuidof(IAudioClient), CLSCTX_ALL, nullptr, spAudioClient.put_void()));

        wil::unique_cotaskmem_ptr<WAVEFORMATEX> spFormat;
        THROW_IF_FAILED(spAudioClient->GetMixFormat(wil::out_param(spFormat)));

        THROW_IF_FAILED(spAudioClient->Initialize(
            AUDCLNT_SHAREMODE_SHARED,
            0,
            RefTimesPerSecond,
            0,
            spFormat.get(),
            nullptr));

        UINT32 numBufferFrames;
        THROW_IF_FAILED(spAudioClient->GetBufferSize(&numBufferFrames));

        wil::com_ptr<IAudioRenderClient> spRenderClient;
        THROW_IF_FAILED(spAudioClient->GetService(__uuidof(IAudioRenderClient), spRenderClient.put_void()));

        // Grab the entire buffer for the initial fill operation.
        BYTE* pData = nullptr;
        THROW_IF_FAILED(spRenderClient->GetBuffer(numBufferFrames, &pData));

        // TODO: Load data from source

        LONG numDataBytes = numBufferFrames * spFormat->nBlockAlign;


    }
}
