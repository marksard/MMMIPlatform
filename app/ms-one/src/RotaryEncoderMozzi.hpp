/*!
 * RotaryEncoderMozzi class
 * Mozziがアナログ対応ピンをハイジャックする対策    
 * Copyright 2023 marksard
 */ 

#pragma once

#include <MozziGuts.h>
#include "../../commonlib/common/RotaryEncoder.hpp"

class RotaryEncoderMozzi : public RotaryEncoder
{
public:
    using RotaryEncoder::init;

    /// @brief ピンモードの指定
    ///        mozziを使っていてanalogピンならANALOG_MOZZIを指定する
    enum class InputPinMode
    {
        DIGITAL,
        ANALOG_MOZZI,
    };

    RotaryEncoderMozzi() {}
    RotaryEncoderMozzi(int pin1, int pin2, InputPinMode pinMode1, InputPinMode pinMode2)
    {
        init(pin1, pin2, pinMode1, pinMode2);
    }

    void init(int pin1, int pin2, InputPinMode pinMode1, InputPinMode pinMode2)
    {
        _pinMode1 = pinMode1;
        _pinMode2 = pinMode2;
        init(pin1, pin2);
    }

protected:
    InputPinMode _pinMode1;
    InputPinMode _pinMode2;

    void getPinValue(byte *pValue1, byte *pValue2) override
    {
        *pValue1 = readPin(_pin1, _pinMode1);
        *pValue2 = readPin(_pin2, _pinMode2);
    }

    inline byte readPin(int pin, InputPinMode pinMode)
    {
        if (pinMode == InputPinMode::ANALOG_MOZZI)
            return (mozziAnalogRead(pin) > 511 ? 1 : 0);
        else
            return digitalRead(pin);
    }
};