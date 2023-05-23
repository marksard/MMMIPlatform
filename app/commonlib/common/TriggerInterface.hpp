/*!
 * TriggerInterface
 * Copyright 2023 marksard
 * This software is released under the MIT license.
 * see https://opensource.org/licenses/MIT
 */ 

#pragma once

#include <Arduino.h>

class TriggerInterface
{
public:
    TriggerInterface() {}
    ~TriggerInterface() {}
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual bool ready() = 0;
    virtual void setMills(int millSec) = 0;
    virtual void setBPM(byte bpm, byte bpmReso) = 0;
};
