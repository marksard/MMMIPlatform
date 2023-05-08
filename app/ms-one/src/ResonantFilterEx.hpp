/*!
 * ResonantFilterEx class
 * ResonantFilterが暴れる対策
 * Copyright 2023 marksard
 */ 

#pragma once

#include <ResonantFilter.h>

/// @brief mozziのResonantFilterをenvelopeで可変にしているとbuf0/buf1の値がマイナスになって動作が狂う
///        適宜リセットしたいので継承してreset関数を追加
/// @tparam su 
/// @tparam FILTER_TYPE 
template <int8_t FILTER_TYPE, typename su = uint8_t>
class ResonantFilterEx : public ResonantFilter<FILTER_TYPE, su>
{
public:
    /// @brief 内部変数をリセット
    inline void reset()
    {
        this->q = 0;
        this->f = 0;
        this->fb = 0;
        this->buf0 = 0;
        this->buf1 = 0;
    }

    /// @brief 最後の状態を取る
    /// @param in 現在の音
    /// @return 最後のフィルターの音
    inline AudioOutputStorage_t last_current(AudioOutputStorage_t in)
    {
        return this->current(in, Int2Type<FILTER_TYPE>());
    }

    /// @brief 音楽的に安定なnext
    /// @param sound フィルターをかける音
    /// @return フィルター済みの音
    inline AudioOutputStorage_t nextSafe(AudioOutputStorage_t sound)
    {
        AudioOutputStorage_t last = last_current(sound);
        // レゾナンス設定によってはフィルターが崩壊しがちなので音量を半分に落として出力もかなり歪むので半分にする
        sound = this->next(sound >> 1) >> 1;
        // 歪みすぎると聴く堪えないので内部データをリセットし前回のフィルター設定のまま鳴らす
        if (sound < -128 || sound > 127)
        {
            Serial.println(last);
            reset();
            sound = last;
        }
        
        return sound;
    }
};
