//--------------------------------------------------------------------------------------------------------------------
// Name        : hal-timer.h
// Purpose     : Hardware Abstraction Layer Timer Port
// Description : 
//               This multi-instance HAL Timer class definition contributes to the HAL of a larger overall project.
//
// Language    : C++
// Platform    : Portable
// Framework   : Portable
// Copyright   : MIT License 2024, John Greenwell
// Requires    : External : Arduino.h
//               Custom   : N/A
//--------------------------------------------------------------------------------------------------------------------
#ifndef _HAL_TIMER_H
#define _HAL_TIMER_H

#include <Arduino.h>

namespace HAL
{

class Timer
{
    public:
        /**
         * @brief Constructor for Timer object
         * @param timer_channel Identifier integer in case multiple timers used.
        */
        Timer(uint8_t timer_channel=0);

        /**
         * @brief Initialize timer
         * @param period_us Timer period in microseconds
        */
        void init(uint32_t period_us) const;

        /**
         * @brief Attach interrupt ISR function to timer
         * @param isr Function to be called every timer period
        */
        void attachInterrupt(void (*isr)()) const;

        /**
         * @brief Start timer
        */
        void start() const;

        /**
         * @brief Stop timer
        */
        void stop() const;

        /**
         * @brief Restart timer
        */
        void restart() const;

    private:
        uint8_t _timer_channel;
};

}

#endif // _HAL_TIMER_H

// EOF
