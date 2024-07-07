//--------------------------------------------------------------------------------------------------------------------
// Name        : hal.h
// Purpose     : Hardware Abstraction Layer
// Description : 
//               This collection of classes is intended to facilitate a hardware abstraction layer for use in
//               embedded projects. It is intended to be modified to suit a particular platform and framework,
//               which allows portability for modules, drivers, and libraries written atop it.
//
//               This interface file should remain as static and backwards compatible as possible. The accompanying
//               source file implementation may change substantially across platforms/frameworks.
//
//               With this method, virtual or expanded pins may be treated as GPIO in an external driver if the HAL
//               is used to abstract its actual implementation. For example, within the driver the pin objects may
//               be HAL::GPIO with an associated pin number. Then, in the HAL source implementation, a check is made
//               for that specific pin identifier and subsequently its actual hardware level behavior is implemented
//               as GPIO, or through a shift register or an IO expander, or as a mock etc.
//
//               Other manner of hardware-specific implemenation details may be hidden in the HAL implmentation. To
//               give another example, the user implementation of a timer ISR may be opaquely wrapped within another
//               method in the HAL source implementation to account for unexpected behaviors of the specific
//               timer hardware that the top-level user application need not be concerned. This is done by attaching
//               the timer interrupt to a function in outer HAL scope and calling by pointer the user's ISR which
//               is also stored in outer scope from within the Timer HAL class.
//
//               See source file hal.cpp for more implementation-specific dependencies.
//
//               TODO: anything c++ that could make this more elegant
//               TODO: consider expanding scope of SPI
//               TODO: expand IO expander functionality e.g. attachInterrupt()
//               TODO: expand HAL GPIO to permit interrupt
//               TODO: update led driver, add GPIO_ prefix to const values in HAL/drivers
//               TODO: consider stripping bus init from the drivers
//               TODO: add null checks in I2C functions, overload simpler ones
//               TODO: adjust all repos to use buses by reference, note init is outside of obj
//               TODO: consider whether bus objects can be const
//
// Language    : C++
// Platform    : Portable
// Framework   : Portable
// Copyright   : MIT License 2024, John Greenwell
// Requires    : External : Arduino.h
//               Custom   : N/A
//--------------------------------------------------------------------------------------------------------------------
#ifndef _HAL_H
#define _HAL_H

#include <Arduino.h>
#include "hal-gpio.h"
#include "hal-gpioport.h"
#include "hal-i2c.h"
#include "hal-spi.h"
#include "hal-timer.h"
#include "hal-uart.h"

namespace HAL
{

/**
 * @brief Delay seconds
 * @param time_s Time in seconds
*/
void delay_s(uint32_t time_s);

/**
 * @brief Delay milliseconds
 * @param time_ms Time in milliseconds
*/
void delay_ms(uint32_t time_ms);

/**
 * @brief Delay microseconds
 * @param time_us Time in microseconds
*/
void delay_us(uint32_t time_us);

/**
 * @brief Processor elapsed time in milliseconds
 * @return Elapsed time in milliseconds since start of timing
*/
uint32_t millis();

/**
 * @brief Processor elapsed time in microseconds
 * @return Elapsed time in microseconds since start of timing
*/
uint32_t micros();

}

#endif // _HAL_H

// EOF
