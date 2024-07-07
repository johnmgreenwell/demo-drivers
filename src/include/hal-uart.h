//--------------------------------------------------------------------------------------------------------------------
// Name        : hal-uart.h
// Purpose     : Hardware Abstraction Layer UART Port
// Description : 
//               This multi-instance HAL UART class definition contributes to the HAL of a larger overall project.
//
// Language    : C++
// Platform    : Portable
// Framework   : Portable
// Copyright   : MIT License 2024, John Greenwell
// Requires    : External : Arduino.h
//               Custom   : N/A
//--------------------------------------------------------------------------------------------------------------------
#ifndef _HAL_UART_H
#define _HAL_UART_H

#include <Arduino.h>

namespace HAL
{

class UART
{
    public:
        /**
         * @brief Constructor for serial object
         * @param serial_channel Identifier integer in case multiple serial objects used
        */
        UART(uint8_t serial_channel=0);

        /**
         * @brief Initialize serial object
         * @param baud Bits per second rate of serial transmission
        */
        void init(uint32_t baud=115200) const;

        /**
         * @brief Read single byte from serial device
        */
        uint8_t read() const;

        /**
         * @brief Read multiple bytes from serial device
         * @param buffer Pointer to buffer into which data is read
         * @param length Number of bytes to read from serial device
        */
       uint32_t readBytes(char *buffer, uint32_t length) const;

        /**
         * @brief Write data to serial device
         * @param str Pointer to string from which data is written
         * @param length Number of bytes to write
        */
        uint32_t write(const char *str, uint32_t length) const;

        /**
         * @brief Write data to serial device
         * @param str Pointer to string from which data is written
         * @param length Number of bytes to write
        */
        uint32_t write(char *str, uint32_t length) const;

        /**
         * @brief Print data to serial device
         * @param str Pointer to string from which data is written
        */
        uint32_t print(const char *str) const;

        /**
         * @brief Print data to serial device
         * @param str Pointer to string from which data is written
        */
        uint32_t print(char *str) const;

        /**
         * @brief Print formatted string to serial device
         * @param str Formatted string to print to serial device
        */
        uint32_t printf(const char *str, ...) const;

        /**
         * @brief Print formatted string to serial device with newline
         * @param str Formatted string to print to serial device
        */
        uint32_t println(const char *str) const;

        /**
         * @brief Check whether data is ready to be read from serial device
        */
        bool available() const;

    private:
        uint8_t _serial_channel;
};

}

#endif // _HAL_UART_H

// EOF
