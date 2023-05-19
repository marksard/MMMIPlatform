/*!
 * Recieve MIDIUSB class
 * Copyright 2023 marksard
 * This software is released under the MIT license.
 * see https://opensource.org/licenses/MIT
 */ 

#pragma once

#include <MIDIUSB.h> // 1.0.5 or later

#define MAX_USBMIDI_NOTE 4

/// @brief MIDIのノートON/OFF管理(MAX_USBMIDI_NOTEノートまでの同時押し対応)
class RecieveMidiUSB
{
public:
    RecieveMidiUSB()
    {
        for (int8_t i = 0; i < MAX_USBMIDI_NOTE; ++i)
            _lastNotes[i] = -1;
        _lastOnNote = 0;
    }

    void setup()
    {
    }

    /// @brief MIDI読み取り
    bool ready()
    {
        _rx = MidiUSB.read();
        return true;
    }

    /// @brief ノートオンしたかどうか
    /// @return true: note on
    bool isNoteOn()
    {
        if (_rx.header != 0x9)
            return false;

        // _lastNotesの状態を更新
        // _lastNotesの空きスペース(-1)に詰める
        for (int8_t i = 0; i < MAX_USBMIDI_NOTE; ++i)
        {
            if (_lastNotes[i] != -1)
                continue;
            _lastNotes[i] = _rx.byte2;
            return true;
        }

        return false;
    }

    /// @brief ノートオフしたかどうか
    /// @return true: note off
    bool isNoteOff()
    {
        if (_rx.header != 0x8)
            return false;

        // _lastNotesの状態を更新
        // _lastNotesにノート情報がひとつでも残っていればfalseとする
        byte result = true;
        for (int8_t i = 0; i < MAX_USBMIDI_NOTE; ++i)
        {
            if (_lastNotes[i] == _rx.byte2)
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
    midiEventPacket_t _rx;
    int8_t _lastNotes[MAX_USBMIDI_NOTE];
    byte _lastOnNote;
};