/*!
 * ButtonMozzi class
 * Mozziがアナログ対応ピンをハイジャックする対策
 * Copyright 2023 marksard
 */ 

#pragma once

#include <MozziGuts.h>
#include "../../commonlib/common/Button.hpp"

class ButtonMozzi : public Button
{
public:
    using Button::init;

    /// @brief ピンモードの指定
    ///        mozziを使っていてanalogピンならANALOG_MOZZIを指定する
    enum class InputPinMode
    {
        DIGITAL,
        ANALOG_MOZZI,
    };

    ButtonMozzi(byte pin, InputPinMode pinMode_)
    {
        init(pin, pinMode_);
    }

    /// @brief ピン設定
    /// @param pin
    /// @param pinMode_
    void init(byte pin, InputPinMode pinMode_)
    {
        _pinMode = pinMode_;
        this->init(pin);
    }

private:
    InputPinMode _pinMode;

    /// @brief ピン値読込
    ///        Analog対応ピンはmozziAnalogReadで読む
    /// @return
    byte readPin() override
    {
        if (_pinMode == InputPinMode::ANALOG_MOZZI)
            return (mozziAnalogRead(_pin) > 511 ? 1 : 0);
        else
            return digitalRead(_pin);
    }
};
