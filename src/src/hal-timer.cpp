//--------------------------------------------------------------------------------------------------------------------
// Name        : hal-timer.cpp
// Purpose     : Hardware Abstraction Layer Timer
// Description : This source file implements header file hal-timer.h.
// Language    : C++
// Platform    : Seeeduino Xiao
// Framework   : Arduino
// Copyright   : MIT License 2024, John Greenwell
//--------------------------------------------------------------------------------------------------------------------

#include <Arduino.h>
#include <TimerTCC0.h>
#include "hal-timer.h"

namespace HAL
{

// Used to wrap the user's timer ISR within a supplemental
void (*userTimerISR)();
void HALTimerISR();

Timer::Timer(uint8_t timer_channel)
: _timer_channel(timer_channel)
{ }

void Timer::init(uint32_t period_us) const
{
    TimerTcc0.initialize(period_us);
}

void Timer::attachInterrupt(void (*isr)()) const
{
    userTimerISR = isr;
    TimerTcc0.attachInterrupt(HALTimerISR);
}

void Timer::start() const
{
    TimerTcc0.start();
}

void Timer::stop() const
{
    TimerTcc0.stop();
}

void Timer::restart() const
{
    TimerTcc0.start();
}

void HALTimerISR()
{
    static uint8_t reset_counter = 0;

    userTimerISR();

    // Timer on the Xiao has proved unstable. Intermittent restart seems to fix this.
    if (100 == reset_counter++)
    {
        TimerTcc0.start();
        reset_counter = 0;
    }
}

}

// EOF
