//--------------------------------------------------------------------------------------------------------------------
// Name        : hal-gpioport.cpp
// Purpose     : Hardware Abstraction Layer GPIO Port
// Description : This source file implements header file hal-gpioport.h.
// Language    : C++
// Platform    : Seeeduino Xiao
// Framework   : Arduino
// Copyright   : MIT License 2024, John Greenwell
//--------------------------------------------------------------------------------------------------------------------

#include <Arduino.h>
#include "hal-gpioport.h"
#include "shift-register.h"
#include "mcp23008.h"

namespace HAL
{

// Drivers handled within the HAL implementation
HAL::I2C i2c_bus(0);
HAL::SPI spi_bus(0);
static const uint8_t               MCP23X08_ADDRESS = 0x20;
static PeripheralIO::ShiftRegister sreg(spi_bus, PIN_A2);
static PeripheralIO::MCP23008      i2c_io(i2c_bus, MCP23X08_ADDRESS);


GPIOPort::GPIOPort(const uint8_t* pins, uint8_t len)
: _pins()
, _n_bits(len)
{
    _n_bits = (len > MAX_PORT_SIZE) ? MAX_PORT_SIZE : len;
    memcpy(_pins, pins, len);
}

void GPIOPort::init() const
{
    if (0 == _pins[0])
        sreg.init();
}

bool GPIOPort::pinMode(uint8_t pin, uint8_t mode) const
{
    return true; // Function not used for this application
}

void GPIOPort::portMode(uint8_t mode) const
{
    if (8 == _pins[0])
        if (GPIO_OUTPUT== mode)
            i2c_io.write(PeripheralIO::MCP23008_IODIR, 0xF0);
        else if (GPIO_INPUT == mode)
            i2c_io.write(PeripheralIO::MCP23008_IODIR, 0xFF);
}

bool GPIOPort::digitalWrite(uint8_t pin, uint8_t val) const
{
    return true; // Function not used for this application
}

uint8_t GPIOPort::digitalRead(uint8_t pin) const
{
    return true; // Function not used for this application
}

void GPIOPort::write(uint32_t val) const
{
    if (0 == _pins[0])
        sreg.write((uint8_t)val);
    else
        i2c_io.write(~(uint8_t)val);
}

uint32_t GPIOPort::read() const
{
    return true; // Function not used for this application
}

}

// EOF
