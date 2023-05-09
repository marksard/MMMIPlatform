/*!
 * Oscillator class
 * 2オシレータをまとめたの
 * Copyright 2023 marksard
 */ 

#pragma once

#include <MozziGuts.h>
#include <Oscil.h>
#include <tables/phasor256_int8.h>
#include <tables/sin256_int8.h>
#include <tables/waveshape1_softclip_int8.h>
#include "ACIDSAW_C.h"
#include "../../commonlib/soundlogic/OscillatorTables.h"

#define OSC_MAX 4

// 電源供給の関係で数%程度変わるので可能なら合わせること(単位：mV)
#define DAC_MAX_MILLVOLT 4800

// テーブルを使う場合（演算が少なくなるので速い）
#define USE_TABLE

class Oscillator
{
public:
    enum class Select
    {
        OSC01,
        OSC02,
    };

    enum class Wave
    {
        SAW,
        SW2,
        SQR,
        SIN,
    };

    Oscillator()
    {
        init();
    }

    void init()
    {
        _wave01 = 0;
        _wave02 = 0;
        _level01 = 4;
        _level02 = 4;
        _vOctCalibration = 100.0;
        _osc01Saw.setTable(PHASOR256_DATA);
        _osc02Saw.setTable(PHASOR256_DATA);
        _osc01Sw2.setTable(ACIDSAW_C_DATA);
        _osc02Sw2.setTable(ACIDSAW_C_DATA);
        _osc01Sqr.setTable(WAVESHAPE1_SOFTCLIP_DATA);
        _osc02Sqr.setTable(WAVESHAPE1_SOFTCLIP_DATA);
        _osc01Sin.setTable(SIN256_DATA);
        _osc02Sin.setTable(SIN256_DATA);
    }

    AudioOutput_t next()
    {
        int16_t osc01Next = waveTable[0][_wave01]->next();
        int16_t osc02Next = waveTable[1][_wave02]->next();
        int16_t sound = (osc01Next >> _level01) + (osc02Next >> _level02);
        return constrain(sound, -128, 127); // as limitter
        // return sound;
    }

    // int count;
    void setFreqFromVOct(Select osc, int16_t vOct, byte oct, byte semi, int16_t add)
    {
#ifdef USE_TABLE
        int freq = pgm_read_float(&octaves[oct]) * pgm_read_float(&semitones[semi]) *
                       pgm_read_float(&volt_table_pow2[vOct]) * _vOctCalibration + add;
#else
        // V/Octは1V上がるごとに1Octave
        // 基準周波数 * pow(2, 電圧)
        int freq = pgm_read_float(&octaves[oct]) * pgm_read_float(&semitones[semi]) *
                       (float)pow(2, map(vOct, 0, 1024, 0, DAC_MAX_MILLVOLT) * 0.001) +
                   add;
#endif
        // if (osc == Select::OSC01)
        // {
        //     count = (count+1)&0x3FF;
        //     if (count == 0)
        //     {
        //         Serial.print(vOct);
        //         Serial.print(",");
        //         Serial.println(freq);
        //     }
        // }

        freq = constrain(freq, 0, 32767);
        int wave = osc == Select::OSC01 ? _wave01 : _wave02;
        waveTable[(int)osc][wave]->setFreq(freq);
    }

    void setFreq_Q16n16(Select osc, byte midiNote, byte oct, byte semi, int16_t add)
    {
        Q16n16 note = Q16n16_mtof(Q8n0_to_Q16n16(((oct + 1) * 12) + semi + midiNote));
        int wave = osc == Select::OSC01 ? _wave01 : _wave02;
        waveTable[(int)osc][wave]->setFreq_Q16n16(note + Q15n0_to_Q15n16(add));
    }

    void setFreq_Q16n16(Select osc, Q16n16 note)
    {
        int wave = osc == Select::OSC01 ? _wave01 : _wave02;
        waveTable[(int)osc][wave]->setFreq_Q16n16(note);
    }

    void setWave(Select osc, Wave wave)
    {
        if (osc == Select::OSC01)
        {
            _wave01 = (int)wave;
        }
        else
        {
            _wave02 = (int)wave;
        }
    }

    void setBalance(byte value)
    {
        value = constrain(value, 0, 8);
        _level01 = _balLevel01[value];
        _level02 = _balLevel02[value];
    }

    void setVOctCalibration(byte value)
    {
        _vOctCalibration = value * 0.01;
    }

private:
    byte _balLevel01[9] = {0, 0, 0, 1, 1, 2, 3, 4, 8};
    byte _balLevel02[9] = {8, 4, 3, 2, 1, 1, 0, 0, 0};

protected:
    int _wave01;
    int _wave02;
    byte _level01;
    byte _level02;
    float _vOctCalibration;

    Oscil<256, AUDIO_RATE> _osc01Saw;
    Oscil<256, AUDIO_RATE> _osc02Saw;
    Oscil<256, AUDIO_RATE> _osc01Sw2;
    Oscil<256, AUDIO_RATE> _osc02Sw2;
    Oscil<256, AUDIO_RATE> _osc01Sqr;
    Oscil<256, AUDIO_RATE> _osc02Sqr;
    Oscil<256, AUDIO_RATE> _osc01Sin;
    Oscil<256, AUDIO_RATE> _osc02Sin;
    Oscil<256, AUDIO_RATE> *waveTable[2][OSC_MAX] =
        {
            {&_osc01Saw, &_osc01Sw2, &_osc01Sqr, &_osc01Sin},
            {&_osc02Saw, &_osc02Sw2, &_osc02Sqr, &_osc02Sin}};
};
