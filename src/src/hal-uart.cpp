//--------------------------------------------------------------------------------------------------------------------
// Name        : hal-uart.cpp
// Purpose     : Hardware Abstraction Layer UART
// Description : This source file implements header file hal-uart.h.
// Language    : C++
// Platform    : Seeeduino Xiao
// Framework   : Arduino
// Copyright   : MIT License 2024, John Greenwell
//--------------------------------------------------------------------------------------------------------------------

#include <Arduino.h>
#include "hal-uart.h"

namespace HAL
{

// Used when wrapping printf()
static char tmp_str[255];

UART::UART(uint8_t serial_channel)
: _serial_channel(serial_channel)
{ }

void UART::init(uint32_t baud) const
{
    Serial.begin(baud);
}

uint8_t UART::read() const
{
    return (uint8_t)Serial.read();
}

uint32_t UART::readBytes(char *buffer, uint32_t length) const
{
    return Serial.readBytes(buffer, length);
}

uint32_t UART::write(const char *str, uint32_t length) const
{
    uint32_t retval = 0;

    for (retval = 0; retval < length; ++retval)
    {
        Serial.write(str[retval]);
    }

    return retval;

    return retval;
}

uint32_t UART::write(char *str, uint32_t length) const
{
    uint32_t retval = 0;

    for (retval = 0; retval < length; ++retval)
    {
        Serial.write(str[retval]);
    }

    return retval;
}

uint32_t UART::print(const char *str) const
{
    return Serial.print(str);
}

uint32_t UART::print(char *str) const
{
    return Serial.print(str);
}

uint32_t UART::printf(const char *str, ...) const
{
    va_list args;
    va_start(args, str);
    vsprintf(tmp_str, str, args);
    return Serial.print(tmp_str);
    va_end(args);
}

uint32_t UART::println(const char *str) const
{
    return Serial.println(str);
}

bool UART::available() const
{
    return Serial.available();
}

}

// EOF
