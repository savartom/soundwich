#pragma once
#include "../common.hpp"
#include <memory>
#include <span>
#include <deque>
#include "IAudioOutput.hpp"
#include <list>
#include <pipewire/pipewire.h>
#include <spa/param/audio/format-utils.h>
#include <algorithm>
#include <vector>


namespace soundwich
{
class PipeWireCore;


class PipeWireOutput : public IAudioOutput
{
    friend class PipeWireCore;
    friend void process(void* core_ptr);
    
public:
    void start() override;
    void pause() override;
    void resume() override;
    void stop() override;
    IAudioOutput& writeSamples(std::vector<float> sample) override;
    audioState getState() override;
    float getNext(); //TODO: can make better
    void setVolume(float newVol);

    ~PipeWireOutput();

private:
    PipeWireOutput();

    PipeWireOutput** it;
    PipeWireCore* core;

    audioState state;

    std::deque<float> data;
    double timer;
    float volume;
};

class PipeWireCore
{
    friend void process(void* core_ptr);

public:
    PipeWireCore();
    PipeWireOutput& createPipeWireOutput();
    ~PipeWireCore();

private:
    pw_thread_loop* loop;
    pw_stream* stream;
    pw_stream_events stream_events;
    std::array<uint8_t, 1024> pod_buffer;
    std::array<PipeWireOutput*, 4096> items;
    uint32_t rate;
    uint32_t channels;
};

void process(void* core_ptr);
}
