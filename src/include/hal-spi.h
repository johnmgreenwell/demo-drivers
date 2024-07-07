//--------------------------------------------------------------------------------------------------------------------
// Name        : hal-spi.h
// Purpose     : Hardware Abstraction Layer SPI Port
// Description : 
//               This multi-instance HAL SPI class definition contributes to the HAL of a larger overall project.
//
// Language    : C++
// Platform    : Portable
// Framework   : Portable
// Copyright   : MIT License 2024, John Greenwell
// Requires    : External : Arduino.h
//               Custom   : N/A
//--------------------------------------------------------------------------------------------------------------------
#ifndef _HAL_SPI_H
#define _HAL_SPI_H

#include <Arduino.h>

namespace HAL
{

class SPI
{
    public:
        /**
         * @brief Constructor for SPI object
         * @param spi_channel Identifier value in case multiple SPI channels used
        */
        SPI(uint8_t spi_channel=0);

        /**
         * @brief SPI initiliaization
        */
        void init(uint32_t baudrate=1000000) const;

        /**
         * @brief SPI generic read-write transfer
         * @param val Value to write to device
         * @return Value read from device
        */
        uint8_t transfer(uint8_t val) const;

    private:
        uint8_t _spi_channel;
};

}

#endif // _HAL_SPI_H

// EOF
