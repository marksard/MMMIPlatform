/*!
 * Marksard Synthesizer One
 * compatible promicro (atmega32u4 5V 16MHz)
 * Mozzi library 1.1.0 or later
 * Tiny4kOLED 2.2.2 or later
 * MIDIUSB 1.0.5 or later
 * Copyright 2023 marksard
 */

///////////////////////////////////////////////////////////////////////////////
// mozzi 1.1.0 or later
// mozzi_config.hのdefineのAUDIO_MODEを直接HIFIに書き換えるとA10からも出力されます
// #include <mozzi_config.h>
// #define AUDIO_MODE HIFI

// #define USE_USB_MIDI
#ifdef USE_USB_MIDI
// #include "../../commonlib/common/RecieveMidiUSB.hpp"
// RecieveMidiUSB rmu;
#include "../../commonlib/common/RecieveMidi.hpp"
RecieveMidi rmu;
#define DELAY_FEEDBACK_MEM 128
#else
#define DELAY_FEEDBACK_MEM 256
#endif

#include <mozzi_midi.h>

#define CONTROL_RATE 512
#include <MozziGuts.h>
#include <Oscil.h>
#include <tables/sin256_int8.h>
#include <ADSR.h>
#include <AudioDelayFeedback.h>
#include "ResonantFilterEx.hpp"
#include "Oscillator.hpp"
#include "../../commonlib/soundlogic/Overdrive.hpp"
#include "EEPROMData.h"
#include "RandomSequencer.hpp"
#include "UI.h"

#define AMOUNT(value, amount, max) ((amount) == 0 ? 0 : ((value) >> ((max) - (amount))))

static Oscillator osc;
static Oscil<SIN256_NUM_CELLS, AUDIO_RATE> lfo01(SIN256_DATA);
static ADSR<CONTROL_RATE, CONTROL_RATE> envFlt;
static ADSR<CONTROL_RATE, CONTROL_RATE> envAmp;
static ResonantFilterEx<LOWPASS> lpf01;
static AudioDelayFeedback<DELAY_FEEDBACK_MEM, ALLPASS> chorus;
static Overdrive overDrive;
static Overdrive limitter;
static AutoRandomSequencer rs;
static byte envFltStep;
static byte envAmpStep;
static int8_t lfo01Step = 0;

UserConfig conf;
SynthPatch patch;

byte seqStart = 0;
byte seqChange = 1;
byte envAmpFree = 0;

///////////////////////////////////////////////////////////////////////////////
/// @brief エンベロープの設定(Sustain省略版)
/// @param pEnv
/// @param attack attack time/level
/// @param decay decaya time/level
/// @param release release time/level
void envSetADR(ADSR<CONTROL_RATE, CONTROL_RATE> *pEnv, int attack, int decay, int release)
{
    // Attack Time, Decay Time, sustainain Level, Release Timeの設定
    // setADLevels(250, 250)の設定に敵わないので固定
    // pEnv->setLevels(decay, min(decay << 1, 255), decay, max(min(decay << 1, release), 1));
    // pEnv->setTimes(max(attack << 2, 1), decay, decay << 8 + decay, max(release << 1, 1));
    pEnv->setADLevels(250, 250);
    pEnv->setTimes(attack, decay, decay == 255 ? 65535 : 0, release);
}

#define GATE_PIN 7
#define VOCT_PIN A7
/// @brief GATE/CV情報受付
void recieveGateCV()
{
    static byte gatePrev = LOW;
    // Gate入力
    byte gate = digitalRead(GATE_PIN);
    if (gate == HIGH && gatePrev == LOW)
    {
        envFlt.noteOn();
        envAmp.noteOn();
    }
    else if (gate == LOW && gatePrev == HIGH)
    {
        envFlt.noteOff();
        envAmp.noteOff();
    }

    gatePrev = gate;

    // CV入力
    int vOct = mozziAnalogRead(VOCT_PIN);
    osc.setFreqFromVOct(Oscillator::Select::OSC01, vOct, patch.osc01_oct, patch.osc01_semi, patch.osc01_detune);
    int add = patch.osc02_detune + AMOUNT((int)lfo01Step, patch.lfo01_amt_osc02, 8);
    osc.setFreqFromVOct(Oscillator::Select::OSC02, vOct, patch.osc02_oct, patch.osc02_semi, add);
}

// #define RX_LED 17
// #define TX_LED 30
/// @brief MIDI情報受付
void recieveMIDI()
{
#ifdef USE_USB_MIDI
    if (rmu.ready())
    {
        if (rmu.isNoteOn())
        {
            envFlt.noteOn();
            envAmp.noteOn();
            // digitalWrite(GATE_PIN, HIGH);
        }
        if (rmu.isNoteOff())
        {
            envFlt.noteOff();
            envAmp.noteOff();
            // digitalWrite(GATE_PIN, LOW);
        }
    }

    byte lastNote = rmu.getNote();
    osc.setFreq_Q16n16(Oscillator::Select::OSC01, lastNote, patch.osc01_oct, patch.osc01_semi, patch.osc01_detune);
    int add = patch.osc02_detune + AMOUNT((int)lfo01Step, patch.lfo01_amt_osc02, 8);
    osc.setFreq_Q16n16(Oscillator::Select::OSC02, lastNote, patch.osc02_oct, patch.osc02_semi, add);
#endif
}

/// @brief ランダムシーケンサ
void randomSequencer()
{
    static byte seq2PPQ = 0;
    static byte lastNote = 0;

    if (seqChange)
    {
        rs.generate();
        seqChange = 0;
    }

    if (rs.ready())
    {
        if (!seqStart)
        {
            seq2PPQ = 0;
            digitalWrite(GATE_PIN, LOW);
            rs.resetSeq();
            envFlt.noteOff();
            envAmp.noteOff();
            return;
        }

        seq2PPQ++;
        if (seq2PPQ & 1)
            digitalWrite(GATE_PIN, HIGH);
        else
            digitalWrite(GATE_PIN, LOW);

        if (rs.isNoteOn())
        {
            lastNote = rs.getNote();
            envFlt.noteOn();
            envAmp.noteOn();
        }
        else
        {
            envFlt.noteOff();
            envAmp.noteOff();
        }
        rs.next(conf.seqMaxStep);
    }

    osc.setFreq_Q16n16(Oscillator::Select::OSC01, lastNote, patch.osc01_oct, patch.osc01_semi, patch.osc01_detune);
    int add = patch.osc02_detune + AMOUNT((int)lfo01Step, patch.lfo01_amt_osc02, 8);
    osc.setFreq_Q16n16(Oscillator::Select::OSC02, lastNote, patch.osc02_oct, patch.osc02_semi, add);
}

///////////////////////////////////////////////////////////////////////////////
// mozzi flow
void setup()
{
    // Serial.begin(4800);
    initEEPROM();
    loadUserConfig(&conf);
    loadSynthPatch(&patch, conf.selectedSlot);

    rs.setBPM(conf.seqBPM);
    rs.start();
    limitter.setParam(4, 2);    // ratio 16:1, threshold 8191

    startMozzi(CONTROL_RATE);

    initOLED();
    initController();

#ifdef USE_USB_MIDI
    rmu.setup();
#endif
}

void updateControl()
{
    static byte lastInputOctVorMIDI = 255;
    // ユーザー操作系更新
    byte changed = updateUserIF();

    if (lastInputOctVorMIDI != conf.inputOctVorMIDI)
    {
        lastInputOctVorMIDI = conf.inputOctVorMIDI;
        pinMode(GATE_PIN, lastInputOctVorMIDI == 0 ? INPUT_PULLUP : OUTPUT);
    }

    // 入力端子、MIDI、シーケンサーからの入力受付、エンベロープとオシレータ周波数の更新
    if (conf.inputOctVorMIDI == 0)
        recieveGateCV();
    else if (conf.inputOctVorMIDI == 1)
        recieveMIDI();
    else
    {
        if (changed)
        {
            rs.setBPM(conf.seqBPM);
            rs.setChangeBar(conf.autoChangeBar);
            rs.autoChanger(conf.autoChange);
        }
        randomSequencer();
    }

    // その他の操作による設定の更新
    if (changed)
    {
        osc.setVOctCalibration(conf.setVOctCalibration);
        osc.setBalance(patch.osc01_vol);
        osc.setWave(Oscillator::Select::OSC01, (Oscillator::Wave)patch.osc01_wave);
        osc.setWave(Oscillator::Select::OSC02, (Oscillator::Wave)patch.osc02_wave);

        // パラメータ更新
        envSetADR(&envFlt, patch.envFlt_attack, patch.envFlt_decay, patch.envFlt_release);
        envSetADR(&envAmp, patch.envAmp_attack, patch.envAmp_decay, patch.envAmp_release);
        lfo01.setFreq((float)(patch.lfo01_freq * 0.05));

        chorus.setFeedbackLevel(patch.chorus_feedback - 128);

        overDrive.setParam(patch.driveLevel, patch.driveLevel);
    }

    // コーラス情報更新
    uint16_t time_amt = constrain(patch.chorus_time + AMOUNT(lfo01Step, patch.lfo01_amt_chorus, 8), 0, 255);
    time_amt = (time_amt << 8) + time_amt; // 8bit持ち上げるだけじゃなく、足してあげないと良い感じにならんので…
    chorus.setDelayTimeCells(time_amt);

    // エンベロープ情報更新
    envFlt.update();
    envAmp.update();
    envFltStep = AMOUNT(envFlt.next(), patch.envFlt_amount, 8);
    envAmpStep = AMOUNT(envAmp.next(), patch.envAmp_amount, 8);

    // フィルター情報更新
    int freq = min(patch.flt_Freq + envFltStep, 255);
    freq = constrain(freq + AMOUNT((int)lfo01Step, patch.lfo01_amt_ffreq, 8), 0, 255);
    lpf01.setCutoffFreqAndResonance(freq, patch.flt_Reso);
}

AudioOutput_t updateAudio()
{
    // LFO更新
    lfo01Step = lfo01.next();
    // サウンド更新
    AudioOutput_t sound = osc.next();
    // ローパスフィルター(int8_t)
    sound = lpf01.nextSafe(sound);
    // アンプエンベロープをかける（int8_t -> int16_tに拡大）
    if (!envAmpFree)
        sound = sound * envAmpStep;
    else
        sound = sound << 7;

    // オーバードライブ
    sound = overDrive.next(sound);
    // 5-8はちょっと増幅しとく
    sound = sound << (patch.driveLevel > 4 ? patch.driveLevel >> 1 : 0);

    // コーラス・フランジャー(入力はint8_tなので8bitシフトして、任意の大きさに戻す)
    if (patch.chorus_level == 8)
    {
        // エフェクト音のみ
        sound = chorus.next(sound >> 8) << 8;
    }
    else if (patch.chorus_level > 0)
    {
        sound = (sound + (chorus.next(sound >> 8) << patch.chorus_level));
    }

    // リミッター
    sound = limitter.next(sound);

    // 最終的にかなり目減りする設定では上げる
    byte bit = patch.driveLevel == 4 || patch.driveLevel > 6 ? 13 : 14;
    return MonoOutput::fromAlmostNBit(bit, sound).clip();
}

void loop()
{
    audioHook(); // required here
}
