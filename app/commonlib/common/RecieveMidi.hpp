/*!
 * Recieve MIDI class
 * Copyright 2023 marksard
 * This software is released under the MIT license.
 * see https://opensource.org/licenses/MIT
 */ 

#pragma once

#include <Arduino.h>
#include <MIDI.h>
#include <HardwareSerial.h>

#define MAX_USBMIDI_NOTE 4

/// @brief MIDIのノートON/OFF管理(MAX_USBMIDI_NOTEノートまでの同時押し対応)
class RecieveMidi
{
public:
    RecieveMidi()
    : midiTransport(Serial1)
    , midiInterface((MidiTransport&)midiTransport)
    {

        for (int8_t i = 0; i < MAX_USBMIDI_NOTE; ++i)
            _lastNotes[i] = -1;
        _lastOnNote = 0;
    }

    void setup()
    {
        midiInterface.begin(1);
    }

    /// @brief MIDI読み取り
    void update()
    {
    }

    /// @brief ノートオンしたかどうか
    /// @return true: note on
    bool isNoteOn()
    {
        if (!midiInterface.read())
            return false;
        // if (midiInterface.getType() != midi::NoteOn)
        //     return false;

        // Serial.print("note on :");
        // Serial.println(midiInterface.getType());
        // _lastNotesの状態を更新
        // _lastNotesの空きスペース(-1)に詰める
        for (int8_t i = 0; i < MAX_USBMIDI_NOTE; ++i)
        {
            if (_lastNotes[i] != -1)
                continue;
            _lastNotes[i] = midiInterface.getData1();
            return true;
        }

        return false;
    }

    /// @brief ノートオフしたかどうか
    /// @return true: note off
    bool isNoteOff()
    {
        if (!midiInterface.read())
            return false;
        // if (midiInterface.getType() != midi::NoteOff)
        //     return false;

        // Serial.print("note off :");
        // Serial.println(midiInterface.getType());

        // _lastNotesの状態を更新
        // _lastNotesにノート情報がひとつでも残っていればfalseとする
        byte result = true;
        for (int8_t i = 0; i < MAX_USBMIDI_NOTE; ++i)
        {
            if (_lastNotes[i] == midiInterface.getData1())
            {
                _lastNotes[i] = -1;
            }
            if (_lastNotes[i] != -1)
            {
                result = false;
            }
        }

        return result;
    }

    /// @brief ノート番号の取得
    ///        _lastNotesの最後から検索して返す
    /// @return MIDIノート番号
    byte getNote()
    {
        for (int8_t i = MAX_USBMIDI_NOTE - 1; i >= 0; --i)
        {
            if (_lastNotes[i] == -1)
                continue;
            _lastOnNote = _lastNotes[i];
            return _lastOnNote;
        }
        
        return _lastOnNote;
    }

private:
    using MidiTransport = MIDI_NAMESPACE::SerialMIDI<HardwareSerial>;
    using MidiInterface = MIDI_NAMESPACE::MidiInterface<MidiTransport>;

    MidiTransport midiTransport;
    MidiInterface midiInterface;

    int8_t _lastNotes[MAX_USBMIDI_NOTE];
    byte _lastOnNote;
};