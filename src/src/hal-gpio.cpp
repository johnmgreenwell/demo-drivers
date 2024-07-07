//--------------------------------------------------------------------------------------------------------------------
// Name        : hal-gpio.cpp
// Purpose     : Hardware Abstraction Layer GPIO
// Description : This source file implements header file hal-gpio.h.
// Language    : C++
// Platform    : Seeeduino Xiao
// Framework   : Arduino
// Copyright   : MIT License 2024, John Greenwell
//--------------------------------------------------------------------------------------------------------------------

#include <Arduino.h>
#include "hal-gpio.h"

namespace HAL
{

GPIO::GPIO(uint8_t pin_number)
: _pin_number(pin_number)
{ }

void GPIO::init(uint8_t pin_number)
{
    _pin_number = pin_number;
}

void GPIO::pinMode(uint8_t mode) const
{
    ::pinMode(_pin_number, mode);
}

void GPIO::digitalWrite(uint8_t val) const
{
    ::digitalWrite(_pin_number, val);
}

uint8_t GPIO::digitalRead() const
{
    return ::digitalRead(_pin_number);
}

}

// EOF
