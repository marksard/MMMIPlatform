#pragma once
#include <Tiny4kOLED_tiny-i2c.h> // 2.2.2 or later
#include <TinyI2CMaster.h>
#include "RotaryEncoderMozzi.hpp"
#include "ButtonMozzi.hpp"
#include "EEPROMData.h"
#include "../../commonlib/soundlogic/OscillatorTables.h"

extern UserConfig conf;
extern UserParameters params;

extern byte seqStart;
extern byte seqChange;

RotaryEncoderMozzi encA(A3, A2, RotaryEncoderMozzi::InputPinMode::ANALOG_MOZZI,
                   RotaryEncoderMozzi::InputPinMode::ANALOG_MOZZI);
RotaryEncoderMozzi encB(A1, A0, RotaryEncoderMozzi::InputPinMode::ANALOG_MOZZI,
                   RotaryEncoderMozzi::InputPinMode::ANALOG_MOZZI);
RotaryEncoderMozzi encC(15, 14, RotaryEncoderMozzi::InputPinMode::DIGITAL,
                   RotaryEncoderMozzi::InputPinMode::DIGITAL);
RotaryEncoderMozzi encD(16, A8, RotaryEncoderMozzi::InputPinMode::DIGITAL,
                   RotaryEncoderMozzi::InputPinMode::ANALOG_MOZZI);

ButtonMozzi btnA(A6, ButtonMozzi::InputPinMode::ANALOG_MOZZI);
ButtonMozzi btnB(5, ButtonMozzi::InputPinMode::DIGITAL);

byte userParamSave = 0;
byte userParamLoad = 0;
byte userParamLoadDef = 0;
byte userConfigSave = 0;
byte oledPow = 1;

///////////////////////////////////////////////////////////////////////////////
// 操作・表示テーブル
#define MENUMAX 10
#define MENUCOL 4
const char title10[] PROGMEM = "RandSequencer";
const char title1[] PROGMEM = "Osc 1        ";
const char title2[] PROGMEM = "Osc 2        ";
const char title3[] PROGMEM = "Filter/OscBal";
const char title4[] PROGMEM = "Filter Env   ";
const char title5[] PROGMEM = "Amp Env      ";
const char title6[] PROGMEM = "LFO          ";
const char title7[] PROGMEM = "Chr/Frng/Gain";
const char title9[] PROGMEM = "Config       ";
const char title8[] PROGMEM = "DataSave/Load";
const char *const titleTable[MENUMAX] PROGMEM =
    {
        title10,
        title1,
        title2,
        title3,
        title4,
        title5,
        title6,
        title7,
        title9,
        title8,
};

const char param10[] PROGMEM = "BPM  step chg  play";
const char param1[] PROGMEM = "wave oct  semi tune";
const char param2[] PROGMEM = "wave oct  semi tune";
const char param3[] PROGMEM = "freq reso 1<>2 ----";
const char param4[] PROGMEM = "attk dcay rels amnt";
const char param5[] PROGMEM = "attk dcay rels amnt";
const char param6[] PROGMEM = "rate >chr >osc >frq";
const char param7[] PROGMEM = "f.bk time amnt driv";
const char param9[] PROGMEM = "step disp c<>m save";
const char param8[] PROGMEM = "slot save load dflt";
const char *const paramTable[MENUMAX] PROGMEM =
    {
        param10,
        param1,
        param2,
        param3,
        param4,
        param5,
        param6,
        param7,
        param9,
        param8,
};

byte nullItem = 0;
byte max_osc = OSC_MAX - 1;
byte max_oct = MAX_OCT - 1;
byte max_semi = MAX_SEMI - 1;
byte max_8bit = 255;
byte max_amnt = 8;
byte max_tune = 10;
byte max_save = 7;
byte min_zero = 0;
byte min_one = 1;
byte max_two = 2;
byte max_four = 4;
byte max_4bit = 16;
byte *valMinMaxSteps[MENUMAX][MENUCOL][3] =
    {
        // min, max, step
        {{&min_one, &max_8bit, &min_one}, {&min_zero, &max_4bit, &min_one}, {&min_zero, &min_one, &min_one}, {&min_zero, &min_one, &min_one}},
        {{&min_zero, &max_osc, &min_one}, {&min_zero, &max_oct, &min_one}, {&min_zero, &max_semi, &min_one}, {&min_zero, &max_tune, &min_one}},
        {{&min_zero, &max_osc, &min_one}, {&min_zero, &max_oct, &min_one}, {&min_zero, &max_semi, &min_one}, {&min_zero, &max_tune, &min_one}},
        {{&min_zero, &max_8bit, &conf.paramStep}, {&min_zero, &max_8bit, &conf.paramStep}, {&min_zero, &max_amnt, &min_one}, {&min_zero, &min_zero, &min_zero}},
        {{&min_zero, &max_8bit, &conf.paramStep}, {&min_zero, &max_8bit, &conf.paramStep}, {&min_zero, &max_8bit, &conf.paramStep}, {&min_zero, &max_amnt, &min_one}},
        {{&min_zero, &max_8bit, &conf.paramStep}, {&min_zero, &max_8bit, &conf.paramStep}, {&min_zero, &max_8bit, &conf.paramStep}, {&min_zero, &max_amnt, &min_one}},
        {{&min_one, &max_8bit, &conf.paramStep}, {&min_zero, &max_amnt, &min_one}, {&min_zero, &max_amnt, &min_one}, {&min_zero, &max_amnt, &min_one}},
        {{&min_zero, &max_8bit, &conf.paramStep}, {&min_zero, &max_8bit, &conf.paramStep}, {&min_zero, &max_amnt, &min_one}, {&min_zero, &max_amnt, &min_one}},
        {{&min_one, &max_8bit, &min_one}, {&min_zero, &min_one, &min_one}, {&min_zero, &max_two, &min_one}, {&min_zero, &min_one, &min_one}},
        {{&min_zero, &max_save, &min_one}, {&min_zero, &min_one, &min_one}, {&min_zero, &min_one, &min_one}, {&min_zero, &min_one, &min_one}},
};

void *valueTable[MENUMAX][MENUCOL] =
    {
        {&conf.seqBPM, &conf.seqMaxStep, &seqChange, &seqStart},
        {&params.osc01_wave, &params.osc01_oct, &params.osc01_semi, &params.osc01_detune},
        {&params.osc02_wave, &params.osc02_oct, &params.osc02_semi, &params.osc02_detune},
        {&params.flt_Freq, &params.flt_Reso, &params.osc01_vol, &nullItem},
        {&params.envFlt_attack, &params.envFlt_decay, &params.envFlt_release, &params.envFlt_amount},
        {&params.envAmp_attack, &params.envAmp_decay, &params.envAmp_release, &params.envAmp_amount},
        {&params.lfo01_freq, &params.lfo01_amt_chorus, &params.lfo01_amt_osc02, &params.lfo01_amt_ffreq},
        {&params.chorus_feedback, &params.chorus_time, &params.chorus_level, &params.driveLevel},
        {&conf.paramStep, &oledPow, &conf.inputOctVorMIDI, &userConfigSave},
        {&conf.selectedSlot, &userParamSave, &userParamLoad, &userParamLoadDef},
};

///////////////////////////////////////////////////////////////////////////////
/// @brief OLED初期化
void initOLED()
{
    // OLED初期化前にI2Cの開始待ちをちゃんとおこなう
    // https://github.com/datacute/Tiny4kOLED/issues/20
    TinyI2C.init();
    while (!TinyI2C.start(0x3C, 0))
    {
        delay(10);
    }
    TinyI2C.stop();
    delay(50);
    // ここからOLED初期化
    oled.begin(sizeof(tiny4koled_init_128x32), tiny4koled_init_128x32);
    oled.setFont(FONT6X8);
    oled.setRotation(180);
    oled.on();
    oled.clear();
    delay(100);
}

/// @brief 操作・表示テーブルの表示
/// @param menuIndex
void dispOLED(byte menuIndex)
{
    static char disp_buf[24] = {0};
    static byte menuIndexPrev = 255; // 初回表示のためハズレ値をいれる
    if (menuIndexPrev != menuIndex)
    {
        menuIndexPrev = menuIndex;
        oled.setCursor(0, 0);
        strcpy_P(disp_buf, (char *)pgm_read_word(&titleTable[menuIndex]));
        oled.print(disp_buf);
        oled.setCursor(0, 1);
        strcpy_P(disp_buf, (char *)pgm_read_word(&paramTable[menuIndex]));
        oled.print(disp_buf);
    }

    sprintf(disp_buf, "%03d  %03d  %03d  %03d",
            *(byte *)(valueTable[menuIndex][0]),
            *(byte *)(valueTable[menuIndex][1]),
            *(byte *)(valueTable[menuIndex][2]),
            *(byte *)(valueTable[menuIndex][3]));
    oled.setCursor(0, 2);
    oled.print(disp_buf);
}

///////////////////////////////////////////////////////////////////////////////
/// @brief 範囲制限サイクリック版
/// @tparam su
/// @param value 検査値
/// @param min 制限範囲の最小値
/// @param max 制限範囲の最大値
/// @return 更新値
template <typename su = uint8_t>
su constrainCyclic(su value, su min, su max)
{
    if (value > max)
        return min;
    if (value < min)
        return max;
    return value;
}

/// @brief 設定情報の更新
byte updateUserIF()
{
    static byte lastStepMin = 0;
    static int menuIndex = 0;
    static byte oledPowLast = 0;
    byte reqUpdateDisp = 0;
    byte reqResetDisp = 0;

    byte stateA = btnA.getState();
    // ボタン操作
    if (stateA == 2)
    {
        menuIndex = constrainCyclic(menuIndex - 1, 0, MENUMAX - 1);
        reqUpdateDisp = 1;
    }
    if (btnB.getState() == 2)
    {
        menuIndex = constrainCyclic(menuIndex + 1, 0, MENUMAX - 1);
        reqUpdateDisp = 1;
    }

    // A長押しでステップ数を1に
    if (stateA == 3 && lastStepMin == 0)
    {
        lastStepMin = conf.paramStep;
        conf.paramStep = 1;
    }
    else if (stateA == 4 && lastStepMin != 0)
    {
        conf.paramStep = lastStepMin;
        lastStepMin = 0;
    }

    // エンコーダー操作
    int8_t enc[4] = {
        (int8_t)encA.getDirection(),
        (int8_t)encB.getDirection(),
        (int8_t)encC.getDirection(),
        (int8_t)encD.getDirection()};
    for (byte i = 0; i < 4; ++i)
    {
        (*(byte *)(valueTable[menuIndex][i])) = constrain(
            (int)*(byte *)(valueTable[menuIndex][i]) +
                (enc[i] *
                 (*(byte *)valMinMaxSteps[menuIndex][i][2])),
            (*(byte *)valMinMaxSteps[menuIndex][i][0]),
            (*(byte *)valMinMaxSteps[menuIndex][i][1]));
        if (enc[i] != 0)
            reqUpdateDisp = 1;
    }

    // Serial.print(enc[0]);
    // Serial.print(",");
    // Serial.print(enc[1]);
    // Serial.print(",");
    // Serial.print(enc[2]);
    // Serial.print(",");
    // Serial.println(enc[3]);

    // 設定保存・呼び出し
    if (userParamLoadDef == 1)
    {
        userParamLoadDef = 0;
        initUserParameters(&params);
        initUserConfig(&conf);
        saveUserConfig(&conf);
        reqResetDisp = 1;
    }
    else if (userParamLoad == 1)
    {
        userParamLoad = 0;
        loadUserParameters(&params, conf.selectedSlot);
        saveSelectedSlot(conf.selectedSlot);
        reqResetDisp = 1;
    }
    else if (userParamSave == 1)
    {
        userParamSave = 0;
        saveUserParameters(&params, conf.selectedSlot);
        saveSelectedSlot(conf.selectedSlot);
        reqResetDisp = 1;
    }
    else if (userConfigSave == 1)
    {
        userConfigSave = 0;
        saveUserConfig(&conf);
        reqResetDisp = 1;
    }

    if (reqResetDisp)
    {
        menuIndex = 0;
        dispOLED(0);
    }
    else if (reqUpdateDisp == 1)
    {
        if (oledPowLast != oledPow)
        {
            oledPowLast = oledPow;
            if (oledPow)
                oled.on();
            else
                oled.off();
        }

        dispOLED(menuIndex);
    }

    return reqResetDisp | reqUpdateDisp;
}
