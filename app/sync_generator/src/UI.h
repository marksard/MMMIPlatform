#pragma once
#include <Tiny4kOLED_tiny-i2c.h> // 2.2.2 or later
#include <TinyI2CMaster.h>
#include "../../commonlib/common/RotaryEncoder.hpp"
#include "../../commonlib/common/Button.hpp"

RotaryEncoder encA(A3, A2);
RotaryEncoder encB(A1, A0);
RotaryEncoder encC(15, 14);
RotaryEncoder encD(16, A8);
Button btnA(A6);
Button btnB(5);

// 表示処理
#define FLIP180 1
#define USE_HW_I2C 1

enum class Mode
{
    SyncGen,
    Midi2Sync,
    None,
};

///////////////////////////////////////////////////////////////////////////////
// 操作・表示テーブル
#define MENUMAX 3
const static char *const titleTable[MENUMAX] =
    {
        "0:Gen 1:MIDI ",
        "SyncGen Conf ",
        "SyncMIDI Conf",
};

const static char *const paramTable[MENUMAX] =
    {
        "Sel  ---- ---- ----",
        "Play BPM  ---- PPQ ",
        "PPQ  ---- Play BPM ",
};

byte valMinMaxSteps[MENUMAX][4][3] =
    {
        // min, max, step
        {{0, 1, 1}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 1, 1}, {60, 250, 1}, {0, 0, 0}, {0, 2, 1}},
        {{0, 1, 1}, {0, 0, 0}, {0, 1, 0}, {0, 255, 0}},
};

extern SyncPulseGenerator syncGen;
extern MidiUsb2SyncPulseGenerator midi2Sync;
extern Mode mode;

int nullItem = 0;
void *valueTable[MENUMAX][4] =
    {
        {&mode, &nullItem, &nullItem, &nullItem},
        {&syncGen._play, &syncGen._bpm, &nullItem, &syncGen._ppqSelect},
        {&midi2Sync._ppqSelect, &nullItem, &midi2Sync._play, &midi2Sync._bpm},
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
        oled.print(titleTable[menuIndex]);
        oled.setCursor(0, 1);
        oled.print(paramTable[menuIndex]);
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
void updateUserIF(byte reqUpdateDisp)
{
    static int menuIndex = 0;

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
                 (valMinMaxSteps[menuIndex][i][2])),
            (valMinMaxSteps[menuIndex][i][0]),
            (valMinMaxSteps[menuIndex][i][1]));
        if (enc[i] != 0)
            reqUpdateDisp = 1;
    }

    // Serial.print(stateA);
    // Serial.print(",");
    // Serial.print(enc[0]);
    // Serial.print(",");
    // Serial.print(enc[1]);
    // Serial.print(",");
    // Serial.print(enc[2]);
    // Serial.print(",");
    // Serial.println(enc[3]);

    if (reqUpdateDisp == 1)
    {
        dispOLED(menuIndex);
    }
}
