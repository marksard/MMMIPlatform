/*!
 * RandomSequencer class
 * 良い感じに適当にシーケンスさせるやつ
 * Copyright 2023 marksard
 */ 

#pragma once

#include <MozziGuts.h>
#include <mozzi_rand.h>
#include <mozzi_utils.h>
#include <EventDelay.h>

#define MAX_SEQ 16
#define MAX_TIMINGS 4
#define MAX_SCALE 8

// フリジアンスケール
const byte scale[MAX_SCALE] PROGMEM =
    {
        0, 1, 3, 5, 7, 8, 10, 12};

// メロディーを成立しやすくするための発音タイミングマップ
// この上にランダムでタイミングを追加してランダムかつメロディーを成立しやすく
const byte timingMap[MAX_TIMINGS][MAX_SEQ] PROGMEM = {
    {1, 0, 1, 1,
     1, 1, 0, 1,
     0, 1, 1, 0,
     1, 0, 0, 1},
    {0, 1, 0, 1,
     1, 0, 1, 0,
     0, 1, 1, 0,
     0, 1, 0, 1},
    {1, 1, 0, 1,
     1, 1, 1, 1,
     1, 1, 1, 1,
     1, 0, 1, 1},
    {1, 0, 1, 0,
     1, 0, 0, 1,
     0, 1, 1, 0,
     1, 0, 0, 1}};

class RandomSequencer
{
public:
    RandomSequencer()
    {
    }

    /// @brief EventDelayに同じ
    /// @return
    bool ready()
    {
        return _ed.ready();
    }

    /// @brief EventDelayに同じ
    void start()
    {
        _ed.start();
    }

    /// @brief 次のステップに遷移
    /// @param endStep 折り返すステップ数
    void next(byte endStep)
    {
        _seqIndex = (_seqIndex + 1) >=
                            (endStep > MAX_SEQ ? MAX_SEQ : endStep)
                        ? 0
                        : (_seqIndex + 1);
        _ed.start();
    }

    /// @brief シーケンスリセット
    /// @return
    void resetSeq()
    {
        _seqIndex = 0;
        _ed.start();
    }

    /// @brief ノートオン状態
    /// @return 1でノートON
    byte isNoteOn()
    {
        return _seq[_seqIndex];
    }

    /// @brief ノート番号取得
    /// @return MIDIノート番号
    byte getNote()
    {
        return _step[_seqIndex];
    }

    /// @brief BPM設定
    /// @param bpm
    void setBPM(byte bpm)
    {
        /// 解像度：16ビート
        uint16_t millis4ppq = BPMtoMillis(bpm * 4);
        _ed.set(millis4ppq);
    }

    /// @brief ランダムシーケンス生成
    void generate()
    {
        randSeed();
        byte seqTimingSelect = rand(MAX_TIMINGS);
        // Serial.println(seqTimingSelect);
        for (byte i = 0; i < MAX_SEQ; ++i)
        {
            // 変更前のメロディーラインをランダムに残して繋がり関連性を持たせる
            if (rand(2))
            {
                continue;
            }

            // 基音(C0) + 音階はスケールに従いつつランダムで + オクターブ上下移動をランダムで(-1 or 0 or 1 * 12)
            _step[i] = 12 + (byte)pgm_read_byte(&scale[rand(MAX_SCALE)]) + (rand(-1, 2) * 12);
            // タイミングマップにランダムでタイミングをorして足す
            _seq[i] = (byte)pgm_read_byte(&timingMap[seqTimingSelect][i]) | (rand(2));
        }
    }

private:
    EventDelay _ed;
    byte _seqIndex = 0;
    byte _step[MAX_SEQ] = {0};
    byte _seq[MAX_SEQ] = {0};
};
