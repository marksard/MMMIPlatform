/*!
 * Oscillator class
 * 2オシレータをまとめたの
 * Copyright 2023 marksard
 */

#pragma once

#include <MozziGuts.h>
#include <mozzi_midi.h>
#include <Oscil.h>
#include <Line.h>
#include <tables/phasor256_int8.h>
#include <tables/sin256_int8.h>
#include <tables/waveshape1_softclip_int8.h>
#include "ACIDSAW_C.h"
#include "../../commonlib/soundlogic/OscillatorTables.h"

#define OSC_MAX 4

// 電源供給の関係で数%程度変わるので可能なら合わせること(単位：mV)
#define DAC_MAX_MILLVOLT 4650

class OscillatorValues
{
public:
    int _wave;
    byte _level;
    float _octSemiValue;
    byte _oct;
    byte _semi;
    Line<Q16n16> _line;

    OscillatorValues()
    {
        _wave = 0;
        _level = 4;
        _octSemiValue = 0.0;
        _oct = 255;
        _semi = 255;
    }
};

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
        _vOctCalibration = 100.0;
        _slideTime = 0;
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
        int16_t osc01Next = waveTable[0][_oscValues[0]._wave]->next();
        int16_t osc02Next = waveTable[1][_oscValues[1]._wave]->next();
        int16_t sound = (osc01Next >> _oscValues[0]._level) +
                        (osc02Next >> _oscValues[1]._level);
        return constrain(sound, -128, 127); // as limitter
        // return sound;
    }

    void setFreqFromVOctCalc(Select osc, int16_t vOct, byte oct, byte semi, int16_t add)
    {
        updateOctSemiValue(osc, oct, semi);
        // V/Octは1V上がるごとに1Octave
        // 基準周波数 * pow(2, 電圧)
        int freq = _oscValues[(int)osc]._octSemiValue *
                       (float)pow(2, map(vOct, 0, 1024, 0, DAC_MAX_MILLVOLT) * 0.001) * _vOctCalibration;
        int wave = _oscValues[(int)osc]._wave;
        waveTable[(int)osc][wave]->setFreq((int)freq + add);
    }

    void setFreqFromVOct(Select osc, int16_t vOct, byte oct, byte semi, int16_t add)
    {
        updateOctSemiValue(osc, oct, semi);
        float freq = _oscValues[(int)osc]._octSemiValue *
                       pgm_read_float(&volt_table_pow2[vOct]) * _vOctCalibration;

        int wave = _oscValues[(int)osc]._wave;
        waveTable[(int)osc][wave]->setFreq((int)freq + add);
        // Q16n16 note = float_to_Q16n16(freq);
        // waveTable[(int)osc][wave]->setFreq_Q16n16(note + Q15n0_to_Q15n16(add));
    }

    void setFreq_Q16n16(Select osc, byte midiNote, byte oct, byte semi, int16_t add)
    {
        Q16n16 note = Q16n16_mtof(Q8n0_to_Q16n16(((oct + 1) * 12) + semi + midiNote));

        if (_slideTime > 0)
        {
            _oscValues[(int)osc]._line.set(note, _slideTime);
            Q16n16 nextNote = _oscValues[(int)osc]._line.next();
            note = nextNote > note ? 
                                max(nextNote, note) : 
                                min(nextNote, note);
        }

        int wave = _oscValues[(int)osc]._wave;
        waveTable[(int)osc][wave]->setFreq_Q16n16(note + Q15n0_to_Q15n16(add));
    }

    void setFreq_Q16n16(Select osc, Q16n16 note)
    {
        int wave = _oscValues[(int)osc]._wave;
        waveTable[(int)osc][wave]->setFreq_Q16n16(note);
    }

    void setWave(Select osc, Wave wave)
    {
        _oscValues[(int)osc]._wave = (int)wave;
    }

    void setBalance(byte value)
    {
        value = constrain(value, 0, 8);
        _oscValues[0]._level = _balLevel01[value];
        _oscValues[1]._level = _balLevel02[value];
    }

    void setVOctCalibration(byte value)
    {
        _vOctCalibration = value * 0.01;
    }

    void setSlideTime(byte slide)
    {
        _slideTime = slide;
    }

private:
    byte _balLevel01[9] = {0, 0, 0, 1, 1, 2, 3, 4, 8};
    byte _balLevel02[9] = {8, 4, 3, 2, 1, 1, 0, 0, 0};

    void updateOctSemiValue(Select osc, byte oct, byte semi)
    {
        // 計算量を減らすため設定変更時のみ再計算
        if (oct != _oscValues[(int)osc]._oct || semi != _oscValues[(int)osc]._semi)
        {
            _oscValues[(int)osc]._oct = oct;
            _oscValues[(int)osc]._semi = semi;
            _oscValues[(int)osc]._octSemiValue = pgm_read_float(&octaves[oct]) * pgm_read_float(&semitones[semi]);
        }
    }

protected:
    byte _slideTime;
    float _vOctCalibration;
    OscillatorValues _oscValues[2];

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
