#include "pch.h"

using namespace winrt;
using namespace Windows::Foundation;

using namespace FourShot::Audio;

int main()
{
    init_apartment();

    AudioEndpointManager manager;
    AudioMixer mixer;

    auto endpoints = manager.Endpoints();
    mixer.Start(endpoints.GetAt(0), endpoints.GetAt(1));
}
