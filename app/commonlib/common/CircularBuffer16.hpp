/*!
 * CircularBuffer16
 * Copyright 2023 marksard
 * This software is released under the MIT license.
 * see https://opensource.org/licenses/MIT
 */ 

#pragma once

#include <Arduino.h>

template <typename T = uint8_t>
class CircularBuffer16
{
public:
    CircularBuffer16()
    {
    }

    void push(T value)
    {
        _buf[_pushIndex] = value;
        _pushIndex = (_pushIndex + 1) & 0x0F;

        // Serial.print("idx: ");
        // Serial.print(_pushIndex);
        // Serial.print(" _buf: ");
        // for (T i = 0; i < 16; ++i)
        // {
        //     Serial.print(_buf[i]);
        //     Serial.print(",");
        // }
        // Serial.println("");
    }

    T pop()
    {
        T result = _buf[_popIndex];
        _buf[_popIndex] = 0;
        T popIndex = (_popIndex + 1) & 0x0F;

        if (_popIndex != _pushIndex)
        {
            _popIndex = popIndex;
        }

        return result;
    }

private:
    T _buf[16] = {0};
    T _pushIndex = 0;
    T _popIndex = 0;
};
