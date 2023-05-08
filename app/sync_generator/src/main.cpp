/*!
 * Sync Generator(Standalone or MIDIUSB sync)
 * compatible promicro (atmega32u4 5V 16MHz)
 * Tiny4kOLED 2.2.2 or later
 * MIDIUSB 1.0.5 or later
 * MsTimer2 1.1 or later
 * Copyright 2023 marksard
 */ 

#include <MsTimer2.h>
#include "SyncPulseGenerator.hpp"
#include "MidiUsb2SyncPulseGenerator.hpp"
#include "UI.h"

#define SYNC_PIN 7

SyncPulseGenerator syncGen(SYNC_PIN);
MidiUsb2SyncPulseGenerator midi2Sync(SYNC_PIN);

byte reqUpdateDisp = 1;
Mode mode = Mode::SyncGen;

void reset()
{
    Serial.print("reset");
    digitalWrite(SYNC_PIN, LOW);
    syncGen.reset();
    midi2Sync.reset();
}

void timerEvent()
{
    if (mode == Mode::SyncGen)
    {
        syncGen.next();
    }
    else if (mode == Mode::Midi2Sync)
    {
        reqUpdateDisp = midi2Sync.next();
    }
}

void setup()
{
    // Serial.begin(1200);
    pinMode(SYNC_PIN, OUTPUT);
    MsTimer2::set(1, timerEvent); // 1ms
    MsTimer2::start();
    initOLED();
}

void loop()
{
    static Mode modeLast = Mode::None;
    updateUserIF(reqUpdateDisp);

    if (modeLast != mode)
    {
        modeLast = mode;
        reset();
    }

    if (mode == Mode::SyncGen)
    {
        syncGen.update();
    }
    else if (mode == Mode::Midi2Sync)
    {
        midi2Sync.update();
    }
}
