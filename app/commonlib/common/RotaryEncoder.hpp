/*!
 * RotaryEncoder class
 * Copyright 2023 marksard
 * This software is released under the MIT license.
 * see https://opensource.org/licenses/MIT
 */

#pragma once

#define RE_DELTA_THRESHOLD_COUNT 5
static const byte _thresholds[RE_DELTA_THRESHOLD_COUNT] = {5, 10, 20, 40, 80};
static const byte _deltas[RE_DELTA_THRESHOLD_COUNT] = {32, 16, 8, 4, 2};

class RotaryEncoder
{
public:
    RotaryEncoder() {}
    RotaryEncoder(int pin1, int pin2)
    {
        init(pin1, pin2);
    }

    /// @brief ピン設定
    /// @param pin1
    /// @param pin2
    void init(int pin1, int pin2)
    {
        _pin1 = pin1;
        _pin2 = pin2;

        pinMode(pin1, INPUT_PULLUP);
        pinMode(pin2, INPUT_PULLUP);

        _timePrev = millis();
        _timeCurrent = _timePrev;

        getDirection(); // 空読みして値をいれておく
    }

    /// @brief 動作方向を取得
    /// @return 0:none 1:clockwise -1:counter clockwise
    int8_t getDirection()
    {
        byte value1, value2;
        getPinValue(&value1, &value2);
        byte state = value1 | (value2 << 1);
        _index = (_index << 2) + (state & 3);
        _index &= 15;

        switch (_index)
        {
        case 0xd:
            return 1;
        case 0x7:
            return -1;
        default:
            return 0;
        }
    }

    /// @brief 動作方向を取得
    /// @return 0:none plus:clockwise minus:counter clockwise
    int8_t getDirectionWithDelta()
    {
        byte value1, value2;
        getPinValue(&value1, &value2);
        byte state = value1 | (value2 << 1);
        _index = (_index << 2) + (state & 3);
        _index &= 15;

        switch (_index)
        {
        case 0xd:
            _timePrev = _timeCurrent;
            _timeCurrent = millis();
            if (_directionPrev == -1 && lastRotationTime() < _thresholds[RE_DELTA_THRESHOLD_COUNT - 1])
                return 1;
            _directionPrev = 1;
            return getDelta();
        case 0x7:
            _timePrev = _timeCurrent;
            _timeCurrent = millis();
            if (_directionPrev == 1 && lastRotationTime() < _thresholds[RE_DELTA_THRESHOLD_COUNT - 1])
                return -1;
            _directionPrev = -1;
            return getDelta() * -1;
        default:
            return 0;
        }
    }

    ulong lastRotationTime()
    {
        return _timeCurrent - _timePrev;
    }

    byte getDelta()
    {
        for (byte i = 0; i < RE_DELTA_THRESHOLD_COUNT; ++i)
        {
            if (lastRotationTime() < _thresholds[i])
            {
                return _deltas[i];
            }
        }

        return 1;
    }

protected:
    byte _pin1;
    byte _pin2;
    byte _index;
    byte _directionPrev;
    ulong _timePrev;
    ulong _timeCurrent;

    virtual void getPinValue(byte *pValue1, byte *pValue2)
    {
        *pValue1 = readPin(_pin1);
        *pValue2 = readPin(_pin2);
    }

    inline byte readPin(int pin)
    {
        return digitalRead(pin);
    }
};
