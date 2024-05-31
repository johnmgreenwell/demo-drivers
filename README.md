# Custom Drivers Demonstration

Custom HAL drivers implementation demo

## Overview

This test project demonstrates the use of custom drivers written for a flexible HAL layer. The [Seeeduino Xiao](https://wiki.seeedstudio.com/Seeeduino-XIAO/) is the microcontroller used as an example platform, and the drivers/devices under test (DUT) are:

* [LED](https://github.com/johnmgreenwell/led)
* [Switch](https://github.com/johnmgreenwell/switch)
* [EEPROM](https://github.com/johnmgreenwell/at24cxx)
* [RTC](https://github.com/johnmgreenwell/ds3232)
* [Temp/humidity sensor](https://github.com/johnmgreenwell/htu21d)
* [SSD1306](https://github.com/johnmgreenwell/ssd1306)
* [7-Segment display](https://github.com/johnmgreenwell/micro7seg)
* [GPIO expander (I2C)](https://github.com/johnmgreenwell/mcp23008)
* [GPIO expander (SPI)](https://github.com/johnmgreenwell/mcp23s08)
* [Shift register](https://github.com/johnmgreenwell/shift-register)

![Example Breadboard](images/custom-drivers-demo_test.png)

Each of the drivers is tested by direct interface or as a subset of another driver. Though the tests are not exhaustive for each driver, they do demonstrate a practical application of each.

## Usage

This project may be build using PlatformIO as provided, with supporting configuration files provided. Each driver is imported as a library dependency, compatible with PlatformIO arrangement. 

## Schematic

The overall schematic for the test setup, along with its associated CAD files are included as composed in KiCad 8.

![Test Setup Schematic](images/custom-drivers-demo_schematic.png)

## License

MIT © 2024 John Greenwell
