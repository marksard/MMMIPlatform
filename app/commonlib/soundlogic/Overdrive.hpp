/*!
 * Overdrive class
 * エンベロープがないコンプレッサーはオーバードライブだよね？
 * Copyright 2023 marksard
 * This software is released under the MIT license.
 * see https://opensource.org/licenses/MIT
 */

#pragma once

#include <arduino.h>

class Overdrive
{
public:
    Overdrive()
    {
        setParam(2, 2);
    }

    void setParam(byte ratio, byte threshold)
    {
        _threshold = 0x7FFF >> threshold;
        _ratio = ratio;
    }

    void update()
    {
    }

    int next(int sound)
    {
        if (abs(sound) > _threshold)
        {
            int16_t peak = abs(sound) - _threshold;
            // スレッショルド以上に飛び出た差分を縮めて歪ませる
            peak = peak >> _ratio;
            int8_t flag = sound < 0 ? -1 : 1;
            sound = (_threshold + peak) * flag;
        }

        return sound;
    }

private:
    uint16_t _threshold;
    byte _ratio;
};
