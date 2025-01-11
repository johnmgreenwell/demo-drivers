//--------------------------------------------------------------------------------------------------------------------
// Name        : hal-i2c.h
// Purpose     : Hardware Abstraction Layer I2C Port
// Description : 
//               This multi-instance HAL I2C class definition contributes to the HAL of a larger overall project.
//
// Language    : C++
// Platform    : Portable
// Framework   : Portable
// Copyright   : MIT License 2024, John Greenwell
// Requires    : External : Arduino.h
//               Custom   : N/A
//--------------------------------------------------------------------------------------------------------------------
#ifndef _HAL_I2C_H
#define _HAL_I2C_H

#include <Arduino.h>

namespace HAL
{

class I2C
{
    public:
        /**
         * @brief Constructor for I2C object
         * @param i2c_channel Identifier value in case multiple I2C channels used
        */
        I2C(uint8_t i2c_channel=0);

        /**
         * @brief I2C initiliaization
         * @param baudrate I2C bus speed
        */
        void init(uint32_t baudrate=100000);

        /**
         * @brief Perform I2C write
         * @param addr Target I2C address
         * @param data Data buffer from which to write 
         * @param len Length of data to write
         * @return Zero for success, nonzero for error
        */
        uint8_t write(uint8_t addr, uint8_t * data, uint32_t len);

        /**
         * @brief Perform an I2C write of a single byte
         * @param addr Target I2C address
         * @param data The data value to write
         * @return Zero for success, nonzero for error
        */
        uint8_t write(uint8_t addr, uint8_t data);

        /**
         * @brief Perform an I2C write of 2 successive bytes
         * @param addr Target I2C address
         * @param reg The register value to write
         * @param data The data value to write
         * @return Zero for success, nonzero for error
        */
        uint8_t write(uint8_t addr, uint8_t reg, uint8_t data);

        /**
         * @brief Perform an I2C write of a uint8_t register value followed by N data
         * @param addr Target I2C address
         * @param reg The uint8_t register value to write
         * @param data Data buffer from which data is written
         * @param len Length of data to write from buffer
         * @return Zero for success, nonzero for error
        */
        uint8_t write(uint8_t addr, uint8_t reg, uint8_t * data, uint32_t len);

        /**
         * @brief Perform an I2C write of a uint16_t register value followed by N data
         * @param addr Target I2C address
         * @param reg The uint16_t register value to write
         * @param data Data buffer from which data is written
         * @param len Length of data to write from buffer
         * @return Zero for success, nonzero for error
        */
        uint8_t write(uint8_t addr, uint16_t reg, uint8_t * data, uint32_t len);

        /**
         * @brief Perform I2C read
         * @param addr Target I2C address
         * @param data Data buffer into which to read
         * @param len Length of data to read
         * @return Zero for success, nonzero for error
        */
        uint8_t read(uint8_t addr, uint8_t * data, uint32_t len);

        /**
         * @brief Read a single I2C byte
         * @param addr Target I2C address
         * @return Single byte read
        */
        uint8_t read(uint8_t addr);

        /**
         * @brief Perform I2C write followed by repeated start read
         * @param addr Target I2C address
         * @param wr_data Data buffer from which to write
         * @param wr_len Length of data to write
         * @param r_data Data buffer into which to read
         * @param r_len Length of data to read
         * @return Zero for success, nonzero for error
        */
        uint8_t writeRead(uint8_t addr, uint8_t * wr_data, uint32_t wr_len, uint8_t * r_data, uint32_t r_len);

        /**
         * @brief Write a single I2C byte followed by a repeated start single byte I2C read
         * @param addr Target I2C address
         * @param reg Register to access
         * @param data Data buffer into which to read
         * @return Zero for success, nonzero for error
        */
        uint8_t writeRead(uint8_t addr, uint8_t reg, uint8_t * data);

        /**
         * @brief Write a single I2C byte followed by a repeated start N byte I2C read
         * @param addr Target I2C address
         * @param reg Register to access (uint8_t)
         * @param data Data buffer into which to read
         * @param len Length of data to read
         * @param stopbit Default/False: repeated start, True: stop, restart
         * @return Zero for success, nonzero for error
        */
        uint8_t writeRead(uint8_t addr, uint8_t reg, uint8_t * data, uint32_t len, bool stopbit=false);

        /**
         * @brief Write two I2C bytes followed by a repeated start N byte I2C read
         * @param addr Target I2C address
         * @param reg Register to access (uint16_t)
         * @param data Data buffer into which to read
         * @param len Length of data to read
         * @return Zero for success, nonzero for error
        */
        uint8_t writeRead(uint8_t addr, uint16_t reg, uint8_t * data, uint32_t len);

        /**
         * @brief Check whether I2C bus is currently in use
         * @return True for busy, false for available
        */
        bool busy() const;

    private:
        uint8_t _i2c_channel;
        uint8_t _i2c_error;
        bool    _i2c_busy;
};

}

#endif // _HAL_I2C_H

// EOF
