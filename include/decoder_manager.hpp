#pragma once
#include "common.hpp"
#include <memory>
#include <string>


namespace soundwich
{

class IDecoder
{
public:
    virtual ~IDecoder() = default;
    virtual bool open(const std::string &path) = 0;
    virtual int readSamples(int16_t *buffer, size_t maxSamples) = 0;
    virtual void close() = 0;
};


class WAVDecoder : public IDecoder
{
public:
    bool open(const std::string &path) override;
    int readSamples(int16_t *buffer, size_t maxSamples) override;
    void close() override;

private:
    FILE *file = nullptr;
    int dataOffset = 0;
    int dataSize = 0;
};


// class MP3Decoder


using IDecoderPtr = std::unique_ptr<IDecoder>;

class DecoderManager
{
public:
    IDecoderPtr createDecoder(const std::string &path);
};

} // namespace soundwich
