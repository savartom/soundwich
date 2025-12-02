//#pragma once
#include "playlist_manager.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>

namespace soundwich
{

void PlaylistManager::load()
    {
        tracks.clear();
        current = 0;  

        std::ifstream in(saveFile);
        if (!in.is_open())
        {
            std::cout << "empty playlist";
            return;
        }

        std::string now_str;
        while(getline(in, now_str)) {
            if (now_str.empty())
            {
                continue;
            }
            Track now;
            now.path = now_str;
            std::filesystem::path p(now_str);
            now.title = p.filename().string();

            // t.durationSeconds = 228 - я хз как измерить длину трека 
            tracks.push_back(now);
        }
    }

void PlaylistManager::save()
    {
       std::ofstream out(saveFile);
        if (!out.is_open())
        {
            std::cout << "error :(";
            return;
        }
        for (const auto &track : tracks)
        {
            out << track.path << '\n';
        }
    }
void PlaylistManager::addTrack(const std::string &path) 
{
    Track now;
    now.path = path;
    std::filesystem::path p(path);
    now.title = p.filename().string();
    // t.durationSeconds = 228 - я хз как измерить длину трека 
    tracks.push_back(now); 
    
}
void PlaylistManager::nextTrack()
    {
       if (tracks.empty()) 
       {
            std::cout << "empty playlist";
            return;
       }
       if (current + 1 < tracks.size())
        {
            ++current;
        }
    }
void PlaylistManager::prevTrack()
    {
       if (tracks.empty()) 
       {
            std::cout << "empty playlist";
            return;
       }
       if (current > 0)
        {
            --current;
        }
    }
void PlaylistManager::deleteTrackByIndex(size_t index) {
    if (index >= tracks.size()) {
        return;
    }
    if (tracks.size() == 1)
    {
        tracks.clear();
        current = 0;
        return;
    }

    if (index < current) {
        --current;
    }
    else if (index == current && index + 1 == tracks.size()) {
        --current;
    }

    tracks.erase(tracks.begin() + static_cast<std::ptrdiff_t>(index));
}

void PlaylistManager::deleteTrackByPath(const std::string &path) {
    for (size_t i = 0; i < tracks.size(); ++i) {
        if (path == tracks[i].path) {
            deleteTrackByIndex(i);
            return;
        }
    }

}
const Track &PlaylistManager::getCurrentTrack() const
{
    if (tracks.empty() || current >= tracks.size())
    {
        throw SoundwichError("No current track");
    }
    return tracks[current];
}

const std::vector<Track> &PlaylistManager::getTracksList() const
{
    return tracks;
}

}

