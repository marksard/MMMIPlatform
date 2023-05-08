/*!
 * MidiUsb2SyncPulseGenerator
 * ms2timerなどで作った1msベースを使って
 * MIDIUSBからのシンク信号をSYNC OUTパルスで送出
 * Copyright 2023 marksard
 */ 

#pragma once

#include "MIDIUSB.h"

struct MidiUsb2SyncPulseGenerator
{
    byte _pin;
    byte _bpm;
    byte _ppqSelect;
    byte _play;
    int _ppqTiming;
    int _fall;
    int _raise;

    byte _bpmLast;
    int _oneSecCount;
    int _bpmCount;

    byte _ppqList[2] = {
        12, // 2ppq
        1   // 24ppq
    };

    MidiUsb2SyncPulseGenerator(byte pin)
    {
        _pin = pin;
        reset();
    }

    void reset()
    {
        _bpm = 0;
        _ppqSelect = 0;
        _play = 0;
        _ppqTiming = 0;
        _fall = 0;
        _raise = 0;

        _bpmLast = 0;
        _oneSecCount = 0;
        _bpmCount = 0;
    }

    void update()
    {
        _ppqTiming = _ppqList[_ppqSelect];
    }
    
    byte next()
    {
        byte reqUpdateDisp = 0;
        if (_play)
        {
            _fall++;
            _oneSecCount++;
        }
        
        midiEventPacket_t rx;
        rx = MidiUSB.read();
        if (rx.header != 0)
        {
            if (!_play)
            {
                // start / continue
                if (rx.byte1 == 0xfa || rx.byte1 == 0xfb)
                {
                    _play = 1;
                    _raise = 0;
                    _fall = 0;
                    _oneSecCount = 0;
                    digitalWrite(_pin, HIGH);
                    reqUpdateDisp = 1;
                }
            }
            else
            {
                // stop
                if (rx.byte1 == 0xfc)
                {
                    _play = 0;
                    digitalWrite(_pin, LOW);
                    reqUpdateDisp = 1;
                }
                // Clock
                if (rx.byte1 == 0xf8)
                {
                    // PPQによってパルスの数を変える
                    _bpmCount++;
                    _raise++;
                    if (_raise >= _ppqTiming)
                    {
                        digitalWrite(_pin, HIGH);
                        _raise = 0;
                        _fall = 0;
                    }
                }
            }
        }

        if (_play)
        {
            // 5ms後にLOW
            if (_fall > 5)
            {
                digitalWrite(_pin, LOW);
            }

            // 約1秒平均のBPMをMIDI Clockのカウント数から算出
            if (_oneSecCount == 1000)
            {
                _bpm = (byte)(_bpmCount / 24.0 * 60.0);
                if (_bpmLast != _bpm)
                {
                    _bpmLast = _bpm;
                    reqUpdateDisp = 1;
                }

                _oneSecCount = 0;
                _bpmCount = 0;
            }
        }

        return reqUpdateDisp;
    }
};
