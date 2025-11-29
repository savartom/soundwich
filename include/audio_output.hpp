#pragma once
#include "common.hpp"
#include <memory>


namespace soundwich
{

class IAudioOutput
{
public:
    virtual ~IAudioOutput() = default;
    virtual bool start() = 0;
    virtual void pause() = 0;
    virtual void resume() = 0;
    virtual void stop() = 0;
    virtual void writeSamples(const int16_t *data, size_t count) = 0;
};


using IAudioOutputPtr = std::unique_ptr<IAudioOutput>;


class PipeWireOutput final : public IAudioOutput
{
public:
    bool start() override;
    void pause() override;
    void resume() override;
    void stop() override;
    void writeSamples(const int16_t *data, size_t count) override;
};

} // namespace soundwich
