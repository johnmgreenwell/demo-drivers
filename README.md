# Custom Drivers Demonstration

Custom HAL drivers implementation demo

## Overview

This test project demonstrates the use of custom drivers written for a flexible HAL layer. The microcontroller used for the core of the design is the [Seeeduino Xiao](https://wiki.seeedstudio.com/Seeeduino-XIAO/), and the devices under test (DUT) are:

* LED
* Switch
* EEPROM
* RTC
* SSD1306
* 7-Segment Display
* GPIO expander (I2C)
* GPIO expander (SPI)
* Shift register

![Example Breadboard](images/custom-drivers-demo_test.png)

Each of the drivers is tested by direct interface or as a subset of another driver. Though the tests are not exhaustive for each driver, they do demonstrate a practical application of each.

## Usage

This project may be build using PlatformIO as provided.

## Schematic

The overall schematic for the test setup, along with its associated CAD files are included as composed in KiCad 8.

![Test Setup Schematic](images/custom-drivers-demo_schematic.png)

## License

MIT © 2024 John Greenwell
