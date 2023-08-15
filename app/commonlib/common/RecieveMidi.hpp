/*!
 * Recieve MIDI class
 * Copyright 2023 marksard
 * This software is released under the MIT license.
 * see https://opensource.org/licenses/MIT
 */

#pragma once

#include <Arduino.h>
#include <MIDI.h>

#include "../../commonlib/common/CircularBuffer16.hpp"

#define MAX_USBMIDI_NOTE 4

/// @brief MIDIのノートON/OFF管理(MAX_USBMIDI_NOTEノートまでの同時押し対応)
class RecieveMidi
{
public:
    RecieveMidi()
        : midiTransport(Serial2), midiInterface((MidiTransport &)midiTransport)
    {

        for (int8_t i = 0; i < MAX_USBMIDI_NOTE; ++i)
            _lastNotes[i] = -1;
        _lastOnNote = 0;
    }

    virtual void setup()
    {
        midiInterface.begin(1);
    }

    /// @brief MIDI読み取り
    bool ready()
    {
        return midiInterface.read();
    }

    /// @brief ノートオンしたかどうか
    /// @return true: note on
    bool isNoteOn()
    {
        if (midiInterface.getType() != midi::NoteOn)
            return false;

        // Serial.print("note on :");
        // Serial.print(midiInterface.getType());
        // Serial.print(",");
        // Serial.print(midiInterface.getData1());
        // Serial.print(",");
        // Serial.println(midiInterface.getData2());

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
        if (midiInterface.getType() != midi::NoteOff)
            return false;

        // Serial.print("note off :");
        // Serial.print(midiInterface.getType());
        // Serial.print(",");
        // Serial.print(midiInterface.getData1());
        // Serial.print(",");
        // Serial.println(midiInterface.getData2());

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

protected:
    using MidiTransport = MIDI_NAMESPACE::SerialMIDI<HardwareSerial>;
    using MidiInterface = MIDI_NAMESPACE::MidiInterface<MidiTransport>;

    MidiTransport midiTransport;
    MidiInterface midiInterface;

    int8_t _lastNotes[MAX_USBMIDI_NOTE];
    byte _lastOnNote;
};

class SendRecvMIDI : public RecieveMidi
{
public:
    SendRecvMIDI(byte midiCh):RecieveMidi()
    {
        _midiCh = midiCh;
    }

    void setup() override
    {
        RecieveMidi::setup();
        midiInterface.sendSystemReset();
        allSoundOff();
    }

    void allSoundOff()
    {
        midiInterface.sendControlChange(120, 0, _midiCh); // All sound off
    }

    void sendClock()
    {
        midiInterface.sendRealTime(midi::MidiType::Clock);
    }

    void noteOn(byte note, byte velo, byte transpose)
    {
        // リングバッファ数を超えたら最初の音をオフにする
        if (noteOnCount >= 15)
        {
            byte note = notesBuf.pop();
            midiInterface.sendNoteOff(note, 0, _midiCh);
            // return;
        }
        byte noteValue = note + transpose;
        midiInterface.sendNoteOn(noteValue, velo, _midiCh);
        // ノートオンとオフは対で対応しないといけないため、バッファに貯めてオフに備える
        notesBuf.push(noteValue);
        noteOnCount++;
        // Serial.print("note on count:");
        // Serial.println(noteOnCount);
    }

    void noteOff()
    {
        // ノートオンしたノートを全部オフにする
        for (byte i = 0; i < noteOnCount; ++i)
        {
            byte note = notesBuf.pop();
            midiInterface.sendNoteOff(note, 0, _midiCh);
            // Serial.print("note off:");
            // Serial.println(note);
        }
        noteOnCount = 0;
    }

private:
    CircularBuffer16<uint8_t> notesBuf;
    byte noteOnCount = 0;
    byte _midiCh = 1;
};
