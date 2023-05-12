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
const static char *UI_VER = "ms01conf_001\0";
struct UserConfig
{
    char ver[14];
    byte selectedSlot;
    byte paramStep;
    byte inputOctVorMIDI; // 0:cv 1:usbmidi 2:randomseq
    byte seqMaxStep;
    byte seqBPM;
    byte setVOctCalibration;
};

// 操作系パラメータ現在値
const static char *PARAM_VER = "ms01param001\0";
struct UserParameters
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
};

// EEPROM格納順番
int startUserConfigAddress = 0;
int startUserParametersAddress = sizeof(UserConfig);

///////////////////////////////////////////////////////////////////////////////
void initUserConfig(UserConfig *pUserConfig)
{
    strcpy(pUserConfig->ver, UI_VER);
    pUserConfig->selectedSlot = -1;
    pUserConfig->paramStep = 8;
    pUserConfig->inputOctVorMIDI = 2;
    pUserConfig->seqMaxStep = 8;
    pUserConfig->seqBPM = 133;
    pUserConfig->setVOctCalibration = 100;
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
void initUserParameters(UserParameters *pParams)
{
    strcpy(pParams->ver, PARAM_VER);
    pParams->osc01_wave = 0;
    pParams->osc01_oct = 1;
    pParams->osc01_semi = 0;
    pParams->osc01_detune = 0;
    pParams->osc01_vol = 4; // osc1/2のバランスで使用

    pParams->osc02_wave = 0;
    pParams->osc02_oct = 2;
    pParams->osc02_semi = 0;
    pParams->osc02_detune = 3;
    pParams->osc02_vol = 0; // 未使用

    pParams->envFlt_attack = 0;
    pParams->envFlt_decay = 80;
    pParams->envFlt_release = 44;
    pParams->envFlt_amount = 7;

    pParams->envAmp_attack = 0;
    pParams->envAmp_decay = 47;
    pParams->envAmp_release = 60;
    pParams->envAmp_amount = 8;

    pParams->lfo01_freq = 1;
    pParams->lfo01_amt_chorus = 0;
    pParams->lfo01_amt_osc02 = 0;
    pParams->lfo01_amt_ffreq = 8;

    pParams->flt_Freq = 47;
    pParams->flt_Reso = 240;

    pParams->chorus_feedback = 127;
    pParams->chorus_time = 127;
    pParams->chorus_level = 7;

    pParams->driveLevel = 0;
}

void loadUserParameters(UserParameters *pParams, int selectSlot)
{
    if (selectSlot == -1)
    {
        initUserParameters(pParams);
        return;
    }

    EEPROM.get<UserParameters>(startUserParametersAddress +
                                   (sizeof(UserParameters) * selectSlot),
                               *pParams);
    if (strcmp(pParams->ver, PARAM_VER))
    {
        initUserParameters(pParams);
    }
}

void saveUserParameters(UserParameters *pParams, int selectSlot)
{
    if (selectSlot == -1)
    {
        return;
    }

    EEPROM.put<UserParameters>(startUserParametersAddress +
                                   (sizeof(UserParameters) * selectSlot),
                               *pParams);
#if defined(ARDUINO_ARCH_RP2040) && !defined(ARDUINO_ARCH_MBED)
    EEPROM.commit();
#endif
}
