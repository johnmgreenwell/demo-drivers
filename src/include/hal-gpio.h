//--------------------------------------------------------------------------------------------------------------------
// Name        : hal-gpio.h
// Purpose     : Hardware Abstraction Layer GPIO
// Description : 
//               This multi-instance HAL GPIO class definition contributes to the HAL of a larger overall project.
//
// Language    : C++
// Platform    : Portable
// Framework   : Portable
// Copyright   : MIT License 2024, John Greenwell
// Requires    : External : Arduino.h
//               Custom   : N/A
//--------------------------------------------------------------------------------------------------------------------
#ifndef _HAL_GPIO_H
#define _HAL_GPIO_H

#include <Arduino.h>

#define GPIO_OUTPUT         OUTPUT
#define GPIO_INPUT          INPUT
#define GPIO_INPUT_PULLUP   INPUT_PULLUP

namespace HAL
{

class GPIO 
{
    public:
        /**
         * @brief Constructor for HAL GPIO object
         * @param pin_number Identifying designator for specific pin
        */
        GPIO(uint8_t pin_number=0);

        /**
         * @brief Used to assign pin number if not accomplished in the constructor
         * @param pin_number Identifying designator for specific pin
        */
        void init(uint8_t pin_number);

        /**
         * @brief Set pin mode (input, output, etc.) of pin
         * @param mode Pin mode; imitates Arduino framework in terms of mode value to behavior
        */
        void pinMode(uint8_t mode) const;

        /**
         * @brief Set logical value of pin
         * @param val Logical value to write to pin; zero for false, nonzero for true
        */
        void digitalWrite(uint8_t val) const;

        /**
         * @brief Read logical value of pin
         * @return Zero for low logic on pin, one for high logic on pin
        */
        uint8_t digitalRead() const;

    private:
        uint8_t _pin_number;
};

}

#endif // _HAL_GPIO_H

// EOF
