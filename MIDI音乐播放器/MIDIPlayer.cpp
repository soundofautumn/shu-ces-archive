//
// Created by Qjming on 2023/6/28.
//
#include "MIDIPlayer.h"
#include "thread"
#include "conio.h"

DWORD MidiOutMessage(HMIDIOUT hMidi, int iStatus, int iChannel, int iFlip, int iVolume);

void print_msg(int track, smf::MidiEvent event);

MIDIPlayer::MIDIPlayer() {
    midiOutOpen(&hMidiOut, MIDIMAPPER, 0, 0, 0);// 打开MIDI播放设备
}

MIDIPlayer::~MIDIPlayer() {
    midiOutClose(hMidiOut);
}

void MIDIPlayer::stop() {
    is_playing = false;
}

void MIDIPlayer::play_track(int track) {
    MidiOutMessage(hMidiOut, 0xC0, track, 0, 0);
    smf::MidiEventList &event_list = midiFile[track];
    DWORD now = 0;
    for (int i = 0; i < event_list.getSize(); ++i) {
        if (!is_playing) {
            break;
        }
        smf::MidiEvent &event = event_list[i];
        std::this_thread::sleep_for(std::chrono::milliseconds((DWORD) (event.seconds * 1000 - now)));
        now = (DWORD) (event.seconds * 1000);
        if (event.isNoteOn()) {
            MidiOutMessage(hMidiOut, 0x90, track, event.getKeyNumber(), event.getVelocity());
        }
        if (event.isNoteOff()) {
            MidiOutMessage(hMidiOut, 0x80, track, event.getKeyNumber(), event.getVelocity());
        }
        if (show_msg) {
            print_msg(track, event);
        }
    }
    this->stop();
}

void MIDIPlayer::play(const char *filename) {
    if (!midiFile.read(filename)) {
        printf("Error: could not read MIDI file.\n");
        return;
    }
    if (play_type == SINGLE_TRACK) {
        midiFile.joinTracks();
    }
    midiFile.doTimeAnalysis();
    is_playing = true;
    for (int track = 0; track < midiFile.getTrackCount(); ++track) {
        std::thread(&MIDIPlayer::play_track, this, track).detach();
    }
    // 按回车键停止播放
    std::thread([this] {
        while (getch() != '\r' && is_playing);
        this->stop();
    }).detach();
    while (is_playing) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

}

DWORD MidiOutMessage(HMIDIOUT hMidi, int iStatus, int iChannel, int iFlip, int iVolume) {
    DWORD dwMessage = (iVolume << 16) | (iFlip << 8) | iStatus | iChannel;
    //                       音量      |     音符     | 状态字节(高4位) | 通道(低4位)
    return midiOutShortMsg(hMidi, dwMessage);
}

void print_msg(int track, smf::MidiEvent event) {
    std::string msg = event.getMetaContent();
    if (event.isNoteOn()) {
        msg = "on";
    }
    if (event.isNoteOff()) {
        msg = "off";
    }
    printf("track %d: | %f seconds | %d key | %d velocity | %s \n",
           track,
           event.seconds,
           event.getKeyNumber(),
           event.getVelocity(),
           msg.c_str());
}
