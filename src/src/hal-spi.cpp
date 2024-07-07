//--------------------------------------------------------------------------------------------------------------------
// Name        : hal-spi.cpp
// Purpose     : Hardware Abstraction Layer SPI
// Description : This source file implements header file hal-spi.h.
// Language    : C++
// Platform    : Seeeduino Xiao
// Framework   : Arduino
// Copyright   : MIT License 2024, John Greenwell
//--------------------------------------------------------------------------------------------------------------------

#include <Arduino.h>
#include <SPI.h>
#include "hal-spi.h"

namespace HAL
{

SPI::SPI(uint8_t spi_channel)
: _spi_channel(spi_channel)
{ }

void SPI::init(uint32_t baudrate) const
{
    (void) baudrate; // Init baudrate not supported in this HAL

    ::SPI.begin();
}

uint8_t SPI::transfer(uint8_t val) const
{
    return ::SPI.transfer(val);
}

}

// EOF
