/*
 * Tiny4kOLED - Drivers for SSD1306 controlled dot matrix OLED/PLED 128x32 displays
 *
 * Based on ssd1306xled, re-written and extended by Stephen Denne
 * from 2017-04-25 at https://github.com/datacute/Tiny4kOLED
 *
 * This file adds support for the I2C implementation from https://github.com/technoblogy/tiny-i2c
 *
 */
#pragma once

#include <Tiny4kOLED_common.h>

class MinimamI2C
{
public:
    MinimamI2C(uint8_t sda, uint8_t scl, uint8_t address)
    {
        _sda_pin = sda;
        _scl_pin = scl;
        _address = address;
    }

    void init()
    {
        pinMode(_sda_pin, INPUT);
        pinMode(_scl_pin, INPUT);
        delay(100);
    }

    bool start()
    {
        while (!digitalRead(_sda_pin) || !digitalRead(_scl_pin))
            ;

        digitalWrite(_sda_pin, LOW);
        pinMode(_sda_pin, OUTPUT);
        delayMicroseconds(1);
        digitalWrite(_scl_pin, LOW);
        pinMode(_scl_pin, OUTPUT);
        delayMicroseconds(1);
        write(_address << 1);
        return true;
    }

    void stop()
    {
        pinMode(_scl_pin, INPUT);
        digitalWrite(_scl_pin, HIGH);
        delayMicroseconds(1);
        pinMode(_sda_pin, INPUT);
        digitalWrite(_sda_pin, HIGH);
        delayMicroseconds(1);
        while (!digitalRead(_sda_pin) || !digitalRead(_scl_pin))
            ;
    }

    bool write(uint8_t byte)
    {
        for (int_fast8_t bit = 7; bit >= 0; bit--)
        {
            if (byte & 128)
            {
                pinMode(_sda_pin, INPUT);
                digitalWrite(_sda_pin, HIGH);
            }
            else
            {
                digitalWrite(_sda_pin, LOW);
                pinMode(_sda_pin, OUTPUT);
            }

            delayMicroseconds(1);
            pinMode(_scl_pin, INPUT);
            digitalWrite(_scl_pin, HIGH);
            delayMicroseconds(1);
            while (!digitalRead(_scl_pin))
                ;

            digitalWrite(_scl_pin, LOW);
            pinMode(_scl_pin, OUTPUT);
            delayMicroseconds(1);
            byte = byte << 1;
        }

        // ACK
        pinMode(_sda_pin, INPUT);
        digitalWrite(_sda_pin, HIGH);
        pinMode(_scl_pin, INPUT);
        digitalWrite(_scl_pin, HIGH);
        delayMicroseconds(1);
        while (!digitalRead(_scl_pin))
            ;

        bool ack = digitalRead(_sda_pin) == 0;
        digitalWrite(_scl_pin, LOW);
        pinMode(_scl_pin, OUTPUT);
        delayMicroseconds(1);
        return ack;
    }

private:
    uint8_t _sda_pin;
    uint8_t _scl_pin;
    uint8_t _address;
};

// #ifdef XIAORP2040
// #define I2C_SDA 6
// #define I2C_SCL 7
// #else
#define I2C_SDA SDA
#define I2C_SCL SCL
// #endif

MinimamI2C MiniI2C(I2C_SDA, I2C_SCL, SSD1306);

static bool datacute_write_tinyi2c(uint8_t byte)
{
    return MiniI2C.write(byte);
}

static uint8_t datacute_endTransmission_tinyi2c(void)
{
    MiniI2C.stop();
    return 0;
}

static bool tiny4koled_beginTransmission_tinyi2c(void)
{
    return MiniI2C.start();
}

static void tiny4koled_begin_tinyi2c(void)
{
    MiniI2C.init();
    while (!tiny4koled_beginTransmission_tinyi2c())
    {
        delay(10);
    }
    datacute_endTransmission_tinyi2c();
}

SSD1306PrintDevice oled(&tiny4koled_begin_tinyi2c, &tiny4koled_beginTransmission_tinyi2c, &datacute_write_tinyi2c, &datacute_endTransmission_tinyi2c);
