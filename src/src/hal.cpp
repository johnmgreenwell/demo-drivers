//--------------------------------------------------------------------------------------------------------------------
// Name        : hal.cpp
// Purpose     : Hardware Abstraction Layer
// Description : This source file implements header file hal.h.
// Language    : C++
// Platform    : Seeeduino Xiao
// Framework   : Arduino
// Copyright   : MIT License 2024, John Greenwell
//--------------------------------------------------------------------------------------------------------------------

#include <Arduino.h>
#include "hal.h"

namespace HAL
{

void delay_s(uint32_t time_s)
{
    for (uint32_t i = 0; i < time_s; i++)
        for (uint16_t j = 0; j < 1000; j++)
            delay(1);
}

void delay_ms(uint32_t time_ms)
{
    for (uint32_t i = 0; i < time_ms; i++)
        delay(1);
}

void delay_us(uint32_t time_us)
{
    for (uint32_t i = 0; i < time_us; i++)
        delayMicroseconds(1);
}

uint32_t millis()
{
    return ::millis();
}

uint32_t micros()
{
    return ::micros();
}

}

// EOF
