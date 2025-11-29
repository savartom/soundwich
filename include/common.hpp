#pragma once
#include <stdexcept>
#include <string>


namespace soundwich
{

struct SoundwichError : public std::runtime_error
{
    explicit SoundwichError(const std::string &msg) : std::runtime_error(msg) {}
};


struct Track
{
    std::string path;
    std::string title;
    int durationSeconds = 0;
};

} // namespace soundwich
