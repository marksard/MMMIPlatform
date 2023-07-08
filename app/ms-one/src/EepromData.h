/*!
 * EEPROM Data
 * 設定まわりの処理のまとめ
 * Copyright 2023 marksard
 */ 

#pragma once

#include <Arduino.h>
#include <EEPROM.h>

void initEEPROM()
{
#if defined(ARDUINO_ARCH_RP2040) && !defined(ARDUINO_ARCH_MBED)
    EEPROM.begin(1024);
#else
    EEPROM.begin();
#endif
}

// 設定値系
const static char *UI_VER = "ms01conf_003\0";
struct UserConfig
{
    char ver[14];
    byte selectedSlot;
    byte inputOctVorMIDI; // 0:cv 1:usbmidi 2:randomseq
    byte seqMaxStep;
    byte seqBPM;
    byte setVOctCalibration;
    byte autoChange;
    byte autoChangeBar;
};

// 操作系パラメータ現在値
const static char *PARAM_VER = "ms01param003\0";
struct SynthPatch
{
    char ver[14];
    byte osc01_wave;
    byte osc01_oct;
    byte osc01_semi;
    byte osc01_detune;
    byte osc01_vol;

    byte osc02_wave;
    byte osc02_oct;
    byte osc02_semi;
    byte osc02_detune;
    byte osc02_vol;

    byte envFlt_attack;
    byte envFlt_decay;
    byte envFlt_release;
    byte envFlt_amount;

    byte envAmp_attack;
    byte envAmp_decay;
    byte envAmp_release;
    byte envAmp_amount;

    byte lfo01_freq;
    byte lfo01_amt_chorus;
    byte lfo01_amt_osc02;
    byte lfo01_amt_ffreq;

    byte flt_Freq;
    byte flt_Reso;

    byte chorus_feedback;
    byte chorus_time;
    byte chorus_level;

    byte driveLevel;
    byte slideTime;
};

// EEPROM格納順番
int startUserConfigAddress = 0;
int startSynthPatchAddress = sizeof(UserConfig);

///////////////////////////////////////////////////////////////////////////////
void initUserConfig(UserConfig *pUserConfig)
{
    strcpy(pUserConfig->ver, UI_VER);
    pUserConfig->selectedSlot = -1;
    pUserConfig->inputOctVorMIDI = 2;
    pUserConfig->seqMaxStep = 8;
    pUserConfig->seqBPM = 133;
    pUserConfig->setVOctCalibration = 100;
    pUserConfig->autoChange = 0;
    pUserConfig->autoChangeBar = 4;
}

void loadUserConfig(UserConfig *pUserConfig)
{
    EEPROM.get<UserConfig>(startUserConfigAddress, *pUserConfig);
    if (strcmp(pUserConfig->ver, UI_VER))
    {
        initUserConfig(pUserConfig);
    }
}

void saveUserConfig(UserConfig *pUserConfig)
{
    EEPROM.put<UserConfig>(startUserConfigAddress, *pUserConfig);
#if defined(ARDUINO_ARCH_RP2040) && !defined(ARDUINO_ARCH_MBED)
    EEPROM.commit();
#endif
}

void saveSelectedSlot(byte selectedSlot)
{
    UserConfig userConfig;
    loadUserConfig(&userConfig);
    userConfig.selectedSlot = selectedSlot;
    saveUserConfig(&userConfig);
}

///////////////////////////////////////////////////////////////////////////////
void initSynthPatch(SynthPatch *pPatch)
{
    strcpy(pPatch->ver, PARAM_VER);
    pPatch->osc01_wave = 0;
    pPatch->osc01_oct = 1;
    pPatch->osc01_semi = 0;
    pPatch->osc01_detune = 0;
    pPatch->osc01_vol = 4; // osc1/2のバランスで使用

    pPatch->osc02_wave = 0;
    pPatch->osc02_oct = 2;
    pPatch->osc02_semi = 0;
    pPatch->osc02_detune = 3;
    pPatch->osc02_vol = 0; // 未使用

    pPatch->envFlt_attack = 0;
    pPatch->envFlt_decay = 80;
    pPatch->envFlt_release = 44;
    pPatch->envFlt_amount = 7;

    pPatch->envAmp_attack = 0;
    pPatch->envAmp_decay = 47;
    pPatch->envAmp_release = 60;
    pPatch->envAmp_amount = 8;

    pPatch->lfo01_freq = 1;
    pPatch->lfo01_amt_chorus = 0;
    pPatch->lfo01_amt_osc02 = 0;
    pPatch->lfo01_amt_ffreq = 8;

    pPatch->flt_Freq = 47;
    pPatch->flt_Reso = 240;

    pPatch->chorus_feedback = 127;
    pPatch->chorus_time = 127;
    pPatch->chorus_level = 7;

    pPatch->driveLevel = 0;
    pPatch->slideTime = 0;
}

void loadSynthPatch(SynthPatch *pPatch, int selectSlot)
{
    if (selectSlot == -1)
    {
        initSynthPatch(pPatch);
        return;
    }

    EEPROM.get<SynthPatch>(startSynthPatchAddress +
                                   (sizeof(SynthPatch) * selectSlot),
                               *pPatch);
    if (strcmp(pPatch->ver, PARAM_VER))
    {
        initSynthPatch(pPatch);
    }
}

void saveSynthPatch(SynthPatch *pPatch, int selectSlot)
{
    if (selectSlot == -1)
    {
        return;
    }

    EEPROM.put<SynthPatch>(startSynthPatchAddress +
                                   (sizeof(SynthPatch) * selectSlot),
                               *pPatch);
#if defined(ARDUINO_ARCH_RP2040) && !defined(ARDUINO_ARCH_MBED)
    EEPROM.commit();
#endif
}
