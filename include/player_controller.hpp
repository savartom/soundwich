#pragma once
#include "audio_output.hpp"
#include "decoder_manager.hpp"
#include "playlist_manager.hpp"


namespace soundwich
{

class PlayerController
{
public:
    PlayerController(PlaylistManager &pm, DecoderManager &dm, IAudioOutput &out);

    void play();
    void pause();
    void resume();
    void nextTrack();
    void prevTrack();

private:
    PlaylistManager &playlist;
    DecoderManager &decoderManager;
    IAudioOutput &audio;

    std::unique_ptr<IDecoder> decoder;
    bool isPaused = false;
    bool isPlaying = false;
};

} // namespace soundwich
