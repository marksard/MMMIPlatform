/*!
 * SequenceGenerator class
 * 良い感じに適当にシーケンスさせるやつ
 * Copyright 2023 marksard
 * This software is released under the MIT license.
 * see https://opensource.org/licenses/MIT
 */

#pragma once

#include <Arduino.h>
#include "../../commonlib/common/PollingTimeEvent.hpp"

#define MAX_SEQ 32
#define MAX_TIMINGS 4
#define MAX_SCALE 8

// フリジアンスケール
const byte scale[MAX_SCALE] PROGMEM =
    {
        0, 1, 3, 5, 7, 8, 10, 12};

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
    SequenceGenerator()
    {
    }

    /// @brief EventDelayに同じ
    /// @return
    virtual bool ready()
    {
        return _pte.ready();
    }

    /// @brief EventDelayに同じ
    void start()
    {
        _pte.start();
    }

    /// @brief 次のステップに遷移
    virtual void next()
    {
        _seqIndex = (_seqIndex + 1) >=
                            (_endStep > MAX_SEQ ? MAX_SEQ : _endStep)
                        ? 0
                        : (_seqIndex + 1);
        // _pte.start();
    }

    /// @brief シーケンスリセット
    /// @return
    virtual void resetSeq()
    {
        _seqIndex = 0;
        _pte.start();
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
        return _note[_seqIndex];
    }

    /// @brief アクセント取得
    /// @return 1でアクセントON
    byte getAcc()
    {
        return _acc[_seqIndex];
    }

    /// @brief BPM設定
    /// @param bpm
    void setBPM(byte bpm)
    {
        /// 解像度：16ビート
        _pte.setBPM(bpm, 4);
    }

    /// @brief 終了ステップ
    /// @param endStep 32まで
    void setEndStep(byte endStep)
    {
        _endStep = constrain(endStep, 1, MAX_SEQ);
    }

    /// @brief ランダムシーケンス生成
    void generate()
    {
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
            _note[i] = 12 + (byte)pgm_read_byte(&scale[random(MAX_SCALE)]) + (random(-1, 2) * 12);
        }

        // 追加でスライドタイミングを適当に追加
        for (byte count = 0; count < 2; ++count)
        {
            byte lastNote = 0;
            byte lastGate = 0;
            for (byte i = random(1, MAX_SEQ - 4); i < MAX_SEQ; ++i)
            {
                // 1オクターブ離れていて、音が鳴る場合
                if (abs(lastNote - _note[i]) >= 12 && lastGate >= 1 && _gate[i] >= 1)
                {
                    // _acc[i - 1] = random(2); // acc
                    _gate[i] = 2; // スライド
                    break;
                }

                lastNote = _note[i];
                lastGate = _gate[i];
            }
        }

        for (byte i = 0; i < MAX_SEQ; ++i)
        {
            Serial.print(_gate[i]);
        }
        Serial.print("   ");
        for (byte i = 0; i < MAX_SEQ; ++i)
        {
            Serial.print(_note[i]);
            Serial.print(", ");
        }
        Serial.println("");
    }

private:
    PollingTimeEvent _pte;
    byte _seqIndex = 0;
    byte _endStep = 0;
    byte _note[MAX_SEQ] = {0};
    byte _gate[MAX_SEQ] = {0};
    byte _acc[MAX_SEQ] = {0};
};

class SequenceAutoChanger : public SequenceGenerator
{
public:
    SequenceAutoChanger() : SequenceGenerator()
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
        if (!result)
            return false;

        // 1小節(_barIndex　16step)でカウント
        if ((_barIndex >> 4) >= _changeBar && _changeStart)
        {
            generate();
            _barIndex = 0;
        }

        // Serial.print(_changeBar);
        // Serial.print(',');
        // Serial.println(_barIndex);

        return result;
    }

    void next() override
    {
        _barIndex++;
        SequenceGenerator::next();
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
