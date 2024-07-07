//--------------------------------------------------------------------------------------------------------------------
// Name        : hal-i2c.cpp
// Purpose     : Hardware Abstraction Layer I2C
// Description : This source file implements header file hal-i2c.h.
// Language    : C++
// Platform    : Seeeduino Xiao
// Framework   : Arduino
// Copyright   : MIT License 2024, John Greenwell
//--------------------------------------------------------------------------------------------------------------------

#include <Arduino.h>
#include <Wire.h>
#include "hal-i2c.h"

namespace HAL
{

// Maximum read buffer size
static const uint8_t I2C_READ_BUFFER_MAX = 32;

I2C::I2C(uint8_t i2c_channel)
: _i2c_channel(i2c_channel)
, _i2c_busy(false)
{ }

void I2C::init(uint32_t baudrate)
{
    if (_i2c_busy) return;

    ::Wire.begin();
    ::Wire.setClock(baudrate);
}

uint8_t I2C::write(uint8_t addr, uint8_t * data, uint32_t len)
{
    if (_i2c_busy) return 1;

    _i2c_busy = true;
    Wire.beginTransmission(addr);
    for (uint8_t iter = 0; iter < len; ++iter)
        Wire.write(data[iter]);
    Wire.endTransmission();
    _i2c_busy = false;

    return 0;
}

uint8_t I2C::write(uint8_t addr, uint8_t data)
{
    if (_i2c_busy) return 1;

    _i2c_busy = true;
    Wire.beginTransmission(addr);
    Wire.write(data);
    Wire.endTransmission();
    _i2c_busy = false;

    return 0;
}

uint8_t I2C::write(uint8_t addr, uint8_t reg, uint8_t data)
{
    if (_i2c_busy) return 1;

    _i2c_busy = true;
    Wire.beginTransmission(addr);
    Wire.write(reg);
    Wire.write(data);
    Wire.endTransmission();
    _i2c_busy = false;

    return 0;
}

uint8_t I2C::write(uint8_t addr, uint8_t reg, uint8_t * data, uint32_t len)
{
    if (_i2c_busy) return 1;

    _i2c_busy = true;
    Wire.beginTransmission(addr);
    Wire.write(reg);
    for (uint8_t iter = 0; iter < len; ++iter)
        Wire.write(data[iter]);
    Wire.endTransmission();
    _i2c_busy = false;

    return 0;
}

uint8_t I2C::write(uint8_t addr, uint16_t reg, uint8_t * data, uint32_t len)
{
    if (_i2c_busy) return 1;

    _i2c_busy = true;
    Wire.beginTransmission(addr);
    Wire.write((uint8_t)(reg >> 8));
    Wire.write((uint8_t)(reg));
    for (uint8_t iter = 0; iter < len; ++iter)
        Wire.write(data[iter]);
    Wire.endTransmission();
    _i2c_busy = false;

    return 0;
}

uint8_t I2C::read(uint8_t addr, uint8_t * data, uint32_t len)
{
    uint32_t bytes_read = 0;
    uint8_t  chunk      = I2C_READ_BUFFER_MAX;

    if (_i2c_busy) return 1;

    _i2c_busy = true;
    Wire.beginTransmission(addr);
    
    while (bytes_read < len)
    {
        chunk = ((len - bytes_read) < I2C_READ_BUFFER_MAX) ? (len - bytes_read) : I2C_READ_BUFFER_MAX;
        Wire.requestFrom(addr, (uint8_t)chunk);
        while ((uint32_t)Wire.available() < chunk); 
        for (uint8_t iter = 0; iter < chunk; ++iter)
            data[iter] = Wire.read();
        bytes_read += chunk;
    }
    
    Wire.endTransmission();
    _i2c_busy = false;

    return 0;
}

uint8_t I2C::read(uint8_t addr)
{
    uint8_t data;

    if (_i2c_busy) return 1;

    _i2c_busy = true;
    Wire.beginTransmission(addr);
    Wire.requestFrom(addr, (uint8_t)1);
    while (!Wire.available()); 
    data = Wire.read();
    Wire.endTransmission();
    _i2c_busy = false;

    return data;
}

uint8_t I2C::writeRead(uint8_t addr, uint8_t * wr_data, uint32_t wr_len, uint8_t * r_data, uint32_t r_len)
{
    uint32_t bytes_read = 0;
    uint8_t  chunk      = I2C_READ_BUFFER_MAX;
    
    if (_i2c_busy) return 1;

    _i2c_busy = true;
    Wire.beginTransmission(addr);
    for (uint8_t iter = 0; iter < wr_len; ++iter)
        Wire.write(wr_data[iter]);
    Wire.endTransmission(0);

    while (bytes_read < r_len)
    {
        chunk = ((r_len - bytes_read) < I2C_READ_BUFFER_MAX) ? (r_len - bytes_read) : I2C_READ_BUFFER_MAX;
        Wire.requestFrom(addr, (uint8_t)chunk);
        while ((uint32_t)Wire.available() < chunk); 
        for (uint32_t iter = bytes_read; iter < (bytes_read + chunk); ++iter)
            r_data[iter] = Wire.read();
        bytes_read += chunk;
    }

    Wire.endTransmission();
    _i2c_busy = false;

    return 0;
}

uint8_t I2C::writeRead(uint8_t addr, uint8_t reg, uint8_t * data)
{
    if (_i2c_busy) return 1;

    _i2c_busy = true;
    Wire.beginTransmission(addr);
    Wire.write(reg);
    Wire.endTransmission(0);
    Wire.requestFrom(addr, (uint8_t)1);
    while (!Wire.available()); 
    *data = Wire.read();
    Wire.endTransmission();
    _i2c_busy = false;

    return 0;
}

uint8_t I2C::writeRead(uint8_t addr, uint8_t reg, uint8_t * data, uint32_t len)
{
    uint32_t bytes_read = 0;
    uint8_t  chunk      = I2C_READ_BUFFER_MAX;

    if (_i2c_busy) return 1;

    _i2c_busy = true;
    Wire.beginTransmission(addr);
    Wire.write((uint8_t)(reg));
    Wire.endTransmission(0);
    
    while (bytes_read < len)
    {
        chunk = ((len - bytes_read) < I2C_READ_BUFFER_MAX) ? (len - bytes_read) : I2C_READ_BUFFER_MAX;
        Wire.requestFrom(addr, (uint8_t)chunk);
        while ((uint32_t)Wire.available() < chunk); 
        for (uint32_t iter = bytes_read; iter < (bytes_read + chunk); ++iter)
            data[iter] = Wire.read();
        bytes_read += chunk;
    }
    
    Wire.endTransmission();
    _i2c_busy = false;

    return 0;
}

uint8_t I2C::writeRead(uint8_t addr, uint16_t reg, uint8_t * data, uint32_t len)
{
    uint32_t bytes_read = 0;
    uint8_t  chunk      = I2C_READ_BUFFER_MAX;

    if (_i2c_busy) return 1;

    _i2c_busy = true;
    Wire.beginTransmission(addr);
    Wire.write((uint8_t)(reg >> 8));
    Wire.write((uint8_t)(reg));
    Wire.endTransmission(0);
    
    while (bytes_read < len)
    {
        chunk = ((len - bytes_read) < I2C_READ_BUFFER_MAX) ? (len - bytes_read) : I2C_READ_BUFFER_MAX;
        Wire.requestFrom(addr, (uint8_t)chunk);
        while ((uint32_t)Wire.available() < chunk); 
        for (uint32_t iter = bytes_read; iter < (bytes_read + chunk); ++iter)
            data[iter] = Wire.read();
        bytes_read += chunk;
    }
    
    Wire.endTransmission();
    _i2c_busy = false;

    return 0;
}

bool I2C::busy() const
{
    return _i2c_busy;
}

}

// EOF
