/*!
 * SyncPulseGenerator
 * ms2timerなどで作った1msベースを使って
 * SYNC OUTパルスで送出
 * Copyright 2023 marksard
 */ 

#pragma once

#include <Arduino.h>

struct SyncPulseGenerator
{
    byte _pin;
    byte _bpm;
    byte _ppqSelect;
    byte _play;
    int _bpmSignalTiming;
    byte _flipSignal;

    byte _ppqList[3] = {
        2, 24, 48
    };

    SyncPulseGenerator(byte pin)
    {
        _pin = pin;
        _bpm = 120;
        _ppqSelect = 0;
        _play = 0;
        _bpmSignalTiming = 120;
        _flipSignal = LOW;
    }

    void reset()
    {
        _ppqSelect = 0;
        _play = 0;
        _flipSignal = LOW;
    }

    void next()
    {
        static int flipCount = 0;
        if (!_play)
        {
            flipCount = 0;
            return;
        }

        // PPQ区間/16の時間に5Vとなるようなデューティー比とした
        flipCount++;
        if ((flipCount >= _bpmSignalTiming && _flipSignal == LOW) ||
            (flipCount >= (_bpmSignalTiming >> 4) && _flipSignal == HIGH))
        {
            _flipSignal = _flipSignal == HIGH ? LOW : HIGH;
            digitalWrite(_pin, _flipSignal);
            if (_flipSignal == HIGH)
            {
                flipCount = 0;
            }
        }
    }

    void update()
    {
        _bpmSignalTiming = (int)((60.0 / _bpm / _ppqList[_ppqSelect]) * 1000.0);
    }
};
