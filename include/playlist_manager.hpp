#pragma once
#include "common.hpp"
#include <string>
#include <vector>


namespace soundwich
{

class PlaylistManager
{
public:
    explicit PlaylistManager(const std::string &savePath);
    ~PlaylistManager();

    void load();
    void save();
    void addTrack(const std::string &path);
    void deleteTrackByPath(const std::string &path);
    void deleteTrackByIndex(size_t index);
    [[nodiscard]] const Track &getCurrentTrack() const;
    [[nodiscard]] const std::vector<Track> &getTracksList() const;
    void nextTrack();
    void prevTrack();

private:
    std::vector<Track> tracks;
    size_t current = 0;
    std::string saveFile;
};

} // namespace soundwich
