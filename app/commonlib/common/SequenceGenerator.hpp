/*!
 * SequenceGenerator class
 * 良い感じに適当にシーケンスさせるやつ
 * Copyright 2023 marksard
 * This software is released under the MIT license.
 * see https://opensource.org/licenses/MIT
 */

#pragma once

#include <Arduino.h>
#include "../../commonlib/common/TriggerInterface.hpp"

#define MAX_SEQ 32
#define MAX_TIMINGS 4
#define MAX_SCALE 8

// スケール
const byte scales[7][MAX_SCALE] PROGMEM =
{
    {0, 2, 4, 5, 7, 9, 11, 12},     // ionian / major
    {0, 2, 3, 5, 7, 9, 10, 12},     // dorian
    {0, 1, 3, 5, 7, 8, 10, 12},     // phrygian
    {0, 2, 4, 6, 7, 9, 11, 12},     // lydian
    {0, 2, 4, 5, 7, 9, 10, 12},     // mixolydian
    {0, 2, 3, 5, 7, 8, 10, 12},     // aeolian / natural minor
    {0, 1, 3, 5, 6, 8, 10, 12},     // locrian
};

// メロディーを成立しやすくするための発音タイミングマップ
// この上にランダムでタイミングを追加してランダムかつメロディーを成立しやすく
const byte gateMap[MAX_TIMINGS][MAX_SEQ] PROGMEM = {
    {1, 0, 1, 1,
     1, 1, 0, 1,
     0, 1, 1, 0,
     1, 0, 0, 1,
     1, 0, 1, 1,
     1, 1, 0, 1,
     0, 1, 1, 0,
     1, 1, 2, 1},
    {0, 1, 0, 1,
     1, 0, 1, 0,
     0, 1, 1, 0,
     0, 1, 0, 1,
     1, 1, 0, 1,
     1, 0, 1, 0,
     0, 1, 2, 0,
     0, 1, 0, 1,},
    {1, 1, 0, 1,
     1, 1, 1, 1,
     1, 1, 1, 1,
     1, 0, 1, 1,
     1, 2, 0, 1,
     1, 1, 1, 2,
     1, 1, 1, 1,
     1, 0, 0, 1},
    {1, 0, 1, 0,
     1, 0, 0, 1,
     0, 1, 1, 0,
     1, 0, 0, 1,
     2, 0, 1, 0,
     1, 0, 0, 1,
     0, 1, 1, 0,
     1, 0, 1, 1}};

// アクセントマップ
const byte accMap[MAX_TIMINGS][MAX_SEQ] PROGMEM = {
    {1, 0, 0, 0,
     0, 0, 0, 1,
     0, 0, 1, 0,
     0, 0, 0, 1,
     1, 0, 0, 0,
     0, 0, 0, 1,
     0, 0, 1, 0,
     0, 0, 1, 0},
    {0, 1, 0, 0,
     1, 0, 0, 0,
     0, 0, 0, 1,
     0, 0, 1, 0,
     0, 1, 0, 0,
     1, 0, 0, 0,
     0, 0, 0, 1,
     0, 0, 1, 1},
    {0, 0, 1, 0,
     0, 1, 0, 0,
     1, 0, 0, 0,
     0, 0, 1, 0,
     0, 0, 1, 0,
     0, 1, 0, 0,
     1, 0, 0, 0,
     1, 0, 1, 0},
    {0, 0, 0, 1,
     0, 0, 1, 0,
     0, 1, 0, 0,
     1, 0, 0, 0,
     0, 0, 0, 1,
     0, 0, 1, 0,
     0, 1, 0, 0,
     1, 0, 0, 1}};

class SequenceGenerator
{
public:
    SequenceGenerator(TriggerInterface *pTrigger)
    {
        _pTrigger = pTrigger;
    }

    /// @brief EventDelayに同じ
    /// @return
    virtual bool ready()
    {
        bool result = _pTrigger->ready();
        // if (result)
        // {
        //     Serial.print("trigger: ");
        //     Serial.println(_seqIndex);
        // }

        return result;
    }

    /// @brief EventDelayに同じ
    void start()
    {
        _pTrigger->start();
    }

    /// @brief EventDelayに同じ
    void stop()
    {
        _pTrigger->stop();
    }

    /// @brief 次のステップに遷移
    virtual void next()
    {
        _seqIndex = (_seqIndex + 1) >=
                            (_endStep > MAX_SEQ ? MAX_SEQ : _endStep)
                        ? 0
                        : (_seqIndex + 1);
        // Serial.println(_seqIndex);
        // _pTrigger->start();
    }

    /// @brief シーケンスリセット
    /// @return
    virtual void resetSeq()
    {
        _seqIndex = 0;
        _pTrigger->start();
    }

    /// @brief ノートオン状態
    /// @return 1でノートON
    byte isNoteOn()
    {
        return _gate[_seqIndex] == 1;
    }

    /// @brief ノートオフ状態
    /// @return 1でノートOFF
    byte isNoteOff()
    {
        return _gate[_seqIndex] == 0;
    }

    /// @brief ノート番号取得
    /// @return MIDIノート番号
    byte getNote()
    {
        return _oct[_seqIndex] + (byte)pgm_read_byte(&scales[_scaleIndex][_note[_seqIndex]]);
    }

    /// @brief アクセント取得
    /// @return 1でアクセントON
    byte getAcc()
    {
        return _acc[_seqIndex];
    }

    /// @brief BPM設定
    /// @param bpm
    void setBPM(byte bpm, byte bpmReso)
    {
        /// 解像度：16ビート
        _pTrigger->setBPM(bpm, bpmReso);
    }

    /// @brief 終了ステップ
    /// @param endStep 32まで
    void setEndStep(byte endStep)
    {
        _endStep = constrain(endStep, 1, MAX_SEQ);
    }

    /// @brief testSeqMode
    /// @param testMode 
    void setTestMode(byte testMode)
    {
        if (_testMode != testMode)
        {
            _testMode = testMode;
            generate();
        }
        
    }

    void setScale(byte scaleIndex)
    {
        _scaleIndex = scaleIndex;
    }

    /// @brief ランダムシーケンス生成
    void generate()
    {
        // 8分Aを4分ごと繰り返し
        if (_testMode)
        {
            for (byte i = 0; i < MAX_SEQ; ++i)
            {
                _gate[i] = (i % 4) == 0 ? 1 : 0;//((i % 4) >= 1) && ((i % 4) <= 2) ? 2 : 0;
                _oct[i] = 0;
                _note[i] = 7;
                _acc[i] = (i % 4) == 0 ? 1 : 0;
            }
            return;
        }

        byte geteSelect = random(MAX_TIMINGS);
        byte veloSelect = random(MAX_TIMINGS);

        randomSeed(micros());

        for (byte i = 0; i < MAX_SEQ; ++i)
        {
            // タイミングマップにランダムでタイミングをorして足す
            _gate[i] = (byte)pgm_read_byte(&gateMap[geteSelect][i]) | (random(2));
            _acc[i] = (byte)pgm_read_byte(&accMap[veloSelect][i]) & (random(2));

            // 変更前のメロディーラインをランダムに残して繋がり関連性を持たせる
            if (random(2))
            {
                continue;
            }

            // 基音(C0) + 音階はスケールに従いつつランダムで + オクターブ上下移動をランダムで(-1 or 0 or 1 * 12)
            // 0 ~ 24 + スケール音
            _oct[i] = 12 + (random(-1, 2) * 12);
            _note[i] = random(MAX_SCALE);
        }

        // 追加でスライドタイミングを適当に追加
        for (byte count = 0; count < 2; ++count)
        {
            byte lastOct = 0;
            byte lastGate = 0;
            for (byte i = random(1, MAX_SEQ - 4); i < MAX_SEQ; ++i)
            {
                // 1オクターブ離れていて、音が鳴る場合
                if (abs(lastOct - _oct[i]) >= 12 && lastGate >= 1 && _gate[i] >= 1)
                {
                    // _acc[i - 1] = random(2); // acc
                    _gate[i] = 2; // スライド
                    break;
                }

                lastOct = _oct[i];
                lastGate = _gate[i];
            }
        }

        // for (byte i = 0; i < MAX_SEQ; ++i)
        // {
        //     Serial.print(_gate[i]);
        // }
        // Serial.print("   ");
        // for (byte i = 0; i < MAX_SEQ; ++i)
        // {
        //     Serial.print(_note[i]);
        //     Serial.print(", ");
        // }
        // Serial.println("");
    }

private:
    TriggerInterface *_pTrigger;
    byte _seqIndex = 0;
    byte _endStep = 0;
    byte _testMode = 0;
    byte _scaleIndex = 2;
    byte _oct[MAX_SEQ] = {0};
    byte _note[MAX_SEQ] = {0};
    byte _gate[MAX_SEQ] = {0};
    byte _acc[MAX_SEQ] = {0};
};

class SequenceAutoChanger : public SequenceGenerator
{
public:
    SequenceAutoChanger(TriggerInterface *pTrigger) : SequenceGenerator(pTrigger)
    {
        _changeBar = 16;
        _changeStart = 0;
        _barIndex = 0;
    }

    void autoChanger(byte on)
    {
        _changeStart = on;
        if (!on)
            _barIndex = 0;
    }

    void setChangeBar(byte changeBar)
    {
        _changeBar = changeBar;
    }

    bool ready() override
    {
        bool result = SequenceGenerator::ready();
        return result;
    }

    void next() override
    {
        _barIndex++;
        SequenceGenerator::next();

        // 1小節(_barIndex　16step)でカウント
        if ((_barIndex >> 4) >= _changeBar && _changeStart)
        {
            generate();
            _barIndex = 0;
        }

        // Serial.print(_changeBar);
        // Serial.print(',');
        // Serial.println(_barIndex);
    }

    void resetSeq() override
    {
        _barIndex = 0;
        SequenceGenerator::resetSeq();
    }

private:
    byte _changeBar;
    byte _changeStart;
    uint16_t _barIndex;
};
