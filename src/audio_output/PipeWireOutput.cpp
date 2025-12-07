#include "audio_output/audio_output.hpp"
#include <iostream>
#include <chrono>

using namespace soundwich;

void PipeWireOutput::start()
{
    if (state == created) state = playing;
}

void PipeWireOutput::pause()
{
    if (state == playing) state = paused;
}

void PipeWireOutput::resume()
{
    if (state == paused) state = playing;
}

void PipeWireOutput::stop()
{
    state = created;
    data.clear();
}

float PipeWireOutput::getNext()
{
    if (data.empty()) return 0;
    float res = *data.begin();
    data.pop_front();
    return res;
}

audioState PipeWireOutput::getState()
{
    return state;
}

IAudioOutput& PipeWireOutput::writeSamples(std::vector<float> sample)
{
    // auto start = std::chrono::high_resolution_clock::now();

    std::ranges::copy(sample, std::back_inserter(data));

    // auto end = std::chrono::high_resolution_clock::now();
    // auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    // std::cout << "copy time: " << milliseconds << '\n';
    return static_cast<IAudioOutput&>(*this);
}

PipeWireOutput::PipeWireOutput() {};

PipeWireOutput::~PipeWireOutput()
{
    *it = nullptr;
    data.clear();
}

void PipeWireOutput::setVolume(float newVal)
{
    volume = newVal;
}
