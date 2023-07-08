#pragma once
#include <MozziGuts.h>
#include <Tiny4kOLED_tiny-i2c.h> // 2.2.2 or later
// #include <TinyI2CMaster.h>
#include "RotaryEncoderMozzi.hpp"
#include "ButtonMozzi.hpp"
#include "EEPROMData.h"
#include "../../commonlib/soundlogic/OscillatorTables.h"

extern UserConfig conf;
extern SynthPatch patch;
extern byte seqStart;
extern byte seqChange;
extern byte envAmpFree;

static RotaryEncoderMozzi encA;
static RotaryEncoderMozzi encB;
static RotaryEncoder encC;
static RotaryEncoder encD;
static Button btnA;
static Button btnB;

static byte isOLEDInit = 0;
static byte userParamSave = 0;
static byte userParamLoad = 0;
static byte userParamLoadDef = 0;
static byte userConfigSave = 0;
static byte oledPow = 1;

///////////////////////////////////////////////////////////////////////////////
// 操作・表示テーブル
#define MENUMAX 11
#define MENUCOL 4
static const char title10[] PROGMEM = "SeqGenerator ";
static const char title11[] PROGMEM = "SeqAutoChange";
static const char title1[] PROGMEM = "Osc 1        ";
static const char title2[] PROGMEM = "Osc 2        ";
static const char title3[] PROGMEM = "Filter/OscSet";
static const char title4[] PROGMEM = "Filter Env   ";
static const char title5[] PROGMEM = "Amp Env      ";
static const char title6[] PROGMEM = "LFO          ";
static const char title7[] PROGMEM = "Chr/Frng/Gain";
static const char title9[] PROGMEM = "Config       ";
static const char title8[] PROGMEM = "DataSave/Load";
static const char *const titleTable[MENUMAX] PROGMEM =
    {
        title10,
        title11,
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

static const char param10[] PROGMEM = "BPM  step chg  play";
static const char param11[] PROGMEM = "SET  bar slid  free";
static const char param1[] PROGMEM = "wave oct  semi tune";
static const char param2[] PROGMEM = "wave oct  semi tune";
static const char param3[] PROGMEM = "freq reso 1<>2 calb";
static const char param4[] PROGMEM = "attk dcay rels amnt";
static const char param5[] PROGMEM = "attk dcay rels amnt";
static const char param6[] PROGMEM = "rate >chr >osc >frq";
static const char param7[] PROGMEM = "f.bk time amnt driv";
static const char param9[] PROGMEM = "step disp c<>m save";
static const char param8[] PROGMEM = "slot save load dflt";
static const char *const paramTable[MENUMAX] PROGMEM =
    {
        param10,
        param11,
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

// static byte nullItem = 0;
static byte max_osc = OSC_MAX - 1;
static byte max_oct = MAX_OCT - 1;
static byte max_semi = MAX_SEMI - 1;
static byte max_8bit = 255;
static byte max_amnt = 8;
static byte max_tune = 10;
static byte max_save = 7;
static byte min_zero = 0;
static byte min_one = 1;
static byte max_two = 2;
// static byte max_four = 4;
static byte max_5bit = 32;
static byte *valMinMaxSteps[MENUMAX][MENUCOL][3] =
    {
        // min, max, step
        {{&min_one, &max_8bit, &min_one}, {&min_zero, &max_5bit, &min_one}, {&min_zero, &min_one, &min_one}, {&min_zero, &min_one, &min_one}},
        {{&min_zero, &min_one, &min_one}, {&min_one, &max_8bit, &min_one}, {&min_zero, &max_5bit, &min_one}, {&min_zero, &min_one, &min_one}},
        {{&min_zero, &max_osc, &min_one}, {&min_zero, &max_oct, &min_one}, {&min_zero, &max_semi, &min_one}, {&min_zero, &max_tune, &min_one}},
        {{&min_zero, &max_osc, &min_one}, {&min_zero, &max_oct, &min_one}, {&min_zero, &max_semi, &min_one}, {&min_zero, &max_tune, &min_one}},
        {{&min_zero, &max_8bit, &conf.paramStep}, {&min_zero, &max_8bit, &conf.paramStep}, {&min_zero, &max_amnt, &min_one}, {&min_zero, &max_8bit, &min_one}},
        {{&min_zero, &max_8bit, &conf.paramStep}, {&min_zero, &max_8bit, &conf.paramStep}, {&min_zero, &max_8bit, &conf.paramStep}, {&min_zero, &max_amnt, &min_one}},
        {{&min_zero, &max_8bit, &conf.paramStep}, {&min_zero, &max_8bit, &conf.paramStep}, {&min_zero, &max_8bit, &conf.paramStep}, {&min_zero, &max_amnt, &min_one}},
        {{&min_one, &max_8bit, &conf.paramStep}, {&min_zero, &max_amnt, &min_one}, {&min_zero, &max_amnt, &min_one}, {&min_zero, &max_amnt, &min_one}},
        {{&min_zero, &max_8bit, &conf.paramStep}, {&min_zero, &max_8bit, &conf.paramStep}, {&min_zero, &max_amnt, &min_one}, {&min_zero, &max_amnt, &min_one}},
        {{&min_one, &max_8bit, &min_one}, {&min_zero, &min_one, &min_one}, {&min_zero, &max_two, &min_one}, {&min_zero, &min_one, &min_one}},
        {{&min_zero, &max_save, &min_one}, {&min_zero, &min_one, &min_one}, {&min_zero, &min_one, &min_one}, {&min_zero, &min_one, &min_one}},
};

static void *valueTable[MENUMAX][MENUCOL] =
    {
        {&conf.seqBPM, &conf.seqMaxStep, &seqChange, &seqStart},
        {&conf.autoChange, &conf.autoChangeBar, &patch.slideTime, &envAmpFree},
        {&patch.osc01_wave, &patch.osc01_oct, &patch.osc01_semi, &patch.osc01_detune},
        {&patch.osc02_wave, &patch.osc02_oct, &patch.osc02_semi, &patch.osc02_detune},
        {&patch.flt_Freq, &patch.flt_Reso, &patch.osc01_vol, &conf.setVOctCalibration},
        {&patch.envFlt_attack, &patch.envFlt_decay, &patch.envFlt_release, &patch.envFlt_amount},
        {&patch.envAmp_attack, &patch.envAmp_decay, &patch.envAmp_release, &patch.envAmp_amount},
        {&patch.lfo01_freq, &patch.lfo01_amt_chorus, &patch.lfo01_amt_osc02, &patch.lfo01_amt_ffreq},
        {&patch.chorus_feedback, &patch.chorus_time, &patch.chorus_level, &patch.driveLevel},
        {&conf.paramStep, &oledPow, &conf.inputOctVorMIDI, &userConfigSave},
        {&conf.selectedSlot, &userParamSave, &userParamLoad, &userParamLoadDef},
};

///////////////////////////////////////////////////////////////////////////////
/// @brief OLED初期化
void initOLED()
{
    // OLED初期化前にI2Cの開始待ちをちゃんとおこなう
    // https://github.com/datacute/Tiny4kOLED/issues/20
    // TinyI2C.init();
    // while (!TinyI2C.start(0x3C, 0))
    // {
    //     delay(10);
    // }
    // TinyI2C.stop();
    // delay(50);
    // ここからOLED初期化
    oled.begin(sizeof(tiny4koled_init_128x32), tiny4koled_init_128x32);
    oled.setFont(FONT6X8);
    oled.setContrast(64);
    oled.setRotation(0);
    oled.on();
    oled.clear();
    delay(100);
    isOLEDInit = 1;
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
        strcpy_P(disp_buf, (const char *)pgm_read_ptr(&titleTable[menuIndex]));
        oled.setCursor(0, 0);
        oled.print(disp_buf);
        strcpy_P(disp_buf, (const char *)pgm_read_ptr(&paramTable[menuIndex]));
        oled.setCursor(0, 1);
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

void initController()
{
    reconnectDigitalIn(A3);
    reconnectDigitalIn(A2);
    reconnectDigitalIn(A1);
    reconnectDigitalIn(A0);
    encA.init(A3, A2, RotaryEncoderMozzi::InputPinMode::ANALOG_MOZZI, RotaryEncoderMozzi::InputPinMode::ANALOG_MOZZI);
    encB.init(A1, A0, RotaryEncoderMozzi::InputPinMode::ANALOG_MOZZI, RotaryEncoderMozzi::InputPinMode::ANALOG_MOZZI);
    encC.init(15, 14);
    encD.init(16, A8);
    btnA.init(A6);
    btnB.init(5);

    btnA.setHoldTime(200);
    btnB.setHoldTime(200);
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

    if (!isOLEDInit)
        return 0;

    byte stateA = btnA.getState();
    byte stateB = btnB.getState();
    // ボタン操作
    if (stateA == 2)
    {
        menuIndex = constrainCyclic(menuIndex - 1, 0, MENUMAX - 1);
        reqUpdateDisp = 1;
    }
    if (stateB == 2)
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
        (int8_t)encA.getDirectionWithDelta(),
        (int8_t)encB.getDirectionWithDelta(),
        (int8_t)encC.getDirectionWithDelta(),
        (int8_t)encD.getDirectionWithDelta()};
    for (byte i = 0; i < 4; ++i)
    {
        (*(byte *)(valueTable[menuIndex][i])) = constrain(
            (int)*(byte *)(valueTable[menuIndex][i]) +
                (enc[i]
                //  *
                //  (*(byte *)valMinMaxSteps[menuIndex][i][2])
                 ),
            (*(byte *)valMinMaxSteps[menuIndex][i][0]),
            (*(byte *)valMinMaxSteps[menuIndex][i][1]));
        if (enc[i] != 0)
            reqUpdateDisp = 1;
    }

    // Serial.print(stateA);
    // Serial.print(",");
    // Serial.print(stateB);
    // Serial.print(",");
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
        initSynthPatch(&patch);
        initUserConfig(&conf);
        saveUserConfig(&conf);
        reqResetDisp = 1;
    }
    else if (userParamLoad == 1)
    {
        userParamLoad = 0;
        loadSynthPatch(&patch, conf.selectedSlot);
        saveSelectedSlot(conf.selectedSlot);
        reqResetDisp = 1;
    }
    else if (userParamSave == 1)
    {
        userParamSave = 0;
        saveSynthPatch(&patch, conf.selectedSlot);
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
