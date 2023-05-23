/*!
 * TriggerInterface
 * Copyright 2023 marksard
 * This software is released under the MIT license.
 * see https://opensource.org/licenses/MIT
 */ 

#pragma once

#include <Arduino.h>
#include "TriggerInterface.hpp"

class SyncInTrigger : public TriggerInterface
{
public:
    SyncInTrigger(byte pin)
    : SyncInTrigger()
    {
        setPin(pin);
    }

    SyncInTrigger()
    {
        _start = 0;
        _pinState = 0;
    }

    void start() override
    {
        pinMode(_pin, INPUT);
        _start = 1;
        _pinState = 0;

    }

    void stop() override
    {
        _start = 0;
        _pinState = 0;
    }

    bool ready() override
    {
        if (!_start) return false;

        bool result = false;
        byte value = readPin();
        // 簡単チャタ取り
        _pinState = (_pinState << 1) | value;
        if (_pinState == 0x80)
        {
            result = true;
        }

        // Serial.println(_pinState);

        return result;
    }

    void setMills(int millSec) override
    {

    }

    void setBPM(byte bpm, byte bpmReso) override
    {

    }

    void setPin(byte pin)
    {
        _pin = pin;
    }

protected:
    byte _start;
    byte _pin;
    byte _pinState;

    /// @brief ピン値読込
    /// @return
    virtual byte readPin()
    {
        return digitalRead(_pin);
    }
};
