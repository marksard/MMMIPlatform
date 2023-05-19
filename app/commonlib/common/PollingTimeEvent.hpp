/*!
 * PollingTimeEvent
 * ポーリングベースのイベント検出クラス
 * Copyright 2023 marksard
 * This software is released under the MIT license.
 * see https://opensource.org/licenses/MIT
 */ 

#pragma once

#include <Arduino.h>

class PollingTimeEvent
{
public:
    PollingTimeEvent()
    {
        _start = 0;
        setBPM(133, 4);
    }

    void start()
    {
        _lastMillis = millis();
        _start = 1;
    }

    void stop()
    {
        _lastMillis = millis();
        _start = 0;
    }

    bool ready()
    {
        if (!_start) return false;

        uint32_t now = millis();
        if (now - _lastMillis >= triggerTime)
        {
            // Serial.print(_lastMillis);
            // Serial.print(",");
            // Serial.print(now);
            // Serial.print(",");
            // Serial.println(triggerTime);
            _lastMillis = now;
            return true;
        }

        return false;
    }

    void setMills(int millSec)
    {
        triggerTime = millSec;
    }

    void setBPM(byte bpm, byte bpmReso)
    {
        triggerTime = (int)((60.0 / (bpm * bpmReso)) * 1000.0);
    }

private:
    byte _start;
    int triggerTime;
    uint32_t _lastMillis;
};
