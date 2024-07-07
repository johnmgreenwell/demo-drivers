//--------------------------------------------------------------------------------------------------------------------
// Name        : hal-gpioport.h
// Purpose     : Hardware Abstraction Layer GPIO Port
// Description : 
//               This multi-instance HAL GPIOPort class definition contributes to the HAL of a larger overall project.
//
// Language    : C++
// Platform    : Portable
// Framework   : Portable
// Copyright   : MIT License 2024, John Greenwell
// Requires    : External : Arduino.h
//               Custom   : N/A
//--------------------------------------------------------------------------------------------------------------------
#ifndef _HAL_GPIOPORT_H
#define _HAL_GPIOPORT_H

#include <Arduino.h>

namespace HAL
{

class GPIOPort
{
    public:
        /**
         * @brief Constructor for HAL GPIOPort object
         * @param pins Array of port's pin ID numbers arranged LSB to MSB of length len
         * @param len Length of port in bits; must not be greater than pin numbers supplied or MAX_PORT_SIZE
        */
        GPIOPort(const uint8_t* pins, uint8_t len);

        /**
         * @brief One-time initialization (e.g. if needed for peripheral GPIO expansion)
        */
        void init() const;

        /**
         * @brief Set input/output mode of individual pin
         * @param pin Pin number of port (0:LSB to n:MSB)
         * @param mode Pin mode; imitates Arduino framework in terms of mode value to behavior
         * @return False for error, true otherwise
        */
        bool pinMode(uint8_t pin, uint8_t mode) const;

        /**
         * @brief Assign same pin mode to entire port
         * @param mode Port mode; imitates Arduino framework in terms of mode value to behavior
        */
        void portMode(uint8_t mode) const;

        /**
         * @brief Write value to individual pin
         * @param pin Pin number of port (0:LSB to n:MSB)
         * @param val Logical value to write to pin; zero for false, nonzero for true
         * @return False for error, true otherwise
        */
        bool digitalWrite(uint8_t pin, uint8_t val) const;

        /**
         * @brief Read value from individual pin
         * @param pin Pin number of port (0:LSB to n:MSB)
         * @return Value read from pin
        */
        uint8_t digitalRead(uint8_t pin) const;

        /**
         * @brief Direct write value to entire port; port must be already configured as output
         * @param val Value to write to port
        */
        void write(uint32_t val) const;

        /**
         * @brief Direct read value from entire GPIO port; port must already be configured as input
         * @return Value read from port
        */
        uint32_t read() const;

    private:
        static const uint8_t MAX_PORT_SIZE = 32;
        uint8_t _pins[MAX_PORT_SIZE];
        uint8_t _n_bits;
};

}

#endif // _HAL_GPIOPORT_H

// EOF
