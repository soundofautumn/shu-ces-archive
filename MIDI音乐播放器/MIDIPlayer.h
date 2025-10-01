//
// Created by Qjming on 2023/6/28.
//

#ifndef MIDIEXAMPLE_MIDIPLAYER_H
#define MIDIEXAMPLE_MIDIPLAYER_H

#include "MidiFile.h"
#include <windows.h>

class MIDIPlayer {
public:
    enum Type {
        SINGLE_TRACK, MULTI_TRACK
    };

    MIDIPlayer();

    ~MIDIPlayer();

    void play(const char *filename);

    void stop();

    bool show_msg = true;

    MIDIPlayer::Type play_type = SINGLE_TRACK;

private:
    void play_track(int track);

    volatile bool is_playing = false;
    HMIDIOUT hMidiOut{};
    smf::MidiFile midiFile;
};

#endif //MIDIEXAMPLE_MIDIPLAYER_H
