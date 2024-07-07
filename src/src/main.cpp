//--------------------------------------------------------------------------------------------------------------------
// Name        : main.cpp
// Purpose     : Test application project
// Description : This main source file supports testing of a lib/module refacting project.
// Platform    : Multiple
// Framework   : Arduino
// Language    : C++
// Copyright   : MIT License 2024, John Greenwell
//--------------------------------------------------------------------------------------------------------------------

#include "hal.h"
#include "led.h"
#include "switch.h"
#include "shift-register.h"
#include "mcp23008.h"
#include "mcp23s08.h"
#include "micro7seg.h"
#include "at24cxx.h"
#include "ds3232.h"
#include "htu21d.h"
#include "ssd1306.h"

// Baud and timer settings
const uint32_t SERIAL_BAUDRATE     = 1000000;
const uint32_t I2C_BAUDRATE        = 100000;
const uint32_t SPI_BAUDRATE        = 1000000;
const uint32_t TIMER_PERIOD_US     = 2500;

// OLED settings
const uint8_t  OLED_SCREEN_WIDTH   = 128;  // OLED width in pixels
const uint8_t  OLED_SCREEN_HEIGHT  = 64;   // OLED height in pixels
const uint8_t  OLED_SCREEN_ADDRESS = 0x3C; // OLED address; see datasheet

// SPI GPIO expander address
const uint8_t  MCP23X08_ADDRESS = 0x20;

// Dummy pin numbers for 7-seg display; actual arrangement handled in the HAL
const uint8_t DISPLAY_PINS_CHAR[8] = {0, 1, 2, 3, 4, 5, 6, 7};
const uint8_t DISPLAY_PINS_SEL[4]  = {8, 9, 10, 11};

// Month name strings
const char *monthName[12] =
{
  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

// Global variables
char data[256];
tmElements_t tm;
time_t current_time;
time_t previous_time;

// HAL-mediated utilities
HAL::Timer timer;

// Peripheral buses
HAL::I2C  i2c_bus(0);
HAL::SPI  spi_bus(0);
HAL::UART serial_bus(0);

// Peripheral objects
PeripheralIO::LED       led(PIN_A1);
PeripheralIO::Switch    button(PIN_A7);
PeripheralIO::MCP23S08  spi_io(spi_bus, PIN_A3, MCP23X08_ADDRESS);
PeripheralIO::Micro7Seg segments(DISPLAY_PINS_CHAR, DISPLAY_PINS_SEL);
PeripheralIO::AT24CXX   eeprom(i2c_bus, PeripheralIO::AT24C256, 0, PIN_A6);
PeripheralIO::DS3232RTC rtc(i2c_bus, PeripheralIO::DS3232RTC::DS32_ADDR);
PeripheralIO::HTU21D    sensor(i2c_bus);
PeripheralIO::SSD1306   display(i2c_bus, OLED_SCREEN_WIDTH, OLED_SCREEN_HEIGHT);

// C library initialization
extern "C" void __libc_init_array(void);

// Weak empty variant initialization function
// May be redefined by variant files
void initVariant() __attribute__((weak));
void initVariant() {}

bool extractTime(const char *str);
bool extractDate(const char *str);
void printInteger(int val, char delim);
void printDate(time_t t);
void printTime(time_t t);
time_t getTime();
void timerISR();

int main()
{
    // Framework initialization
    init();
    __libc_init_array();
    initVariant();

#if defined(USBCON)
    USBDevice.init();
    USBDevice.attach();
#endif

    // Bus initialization
    serial_bus.init(SERIAL_BAUDRATE);
    i2c_bus.init(I2C_BAUDRATE);
    spi_bus.init(SPI_BAUDRATE);

    HAL::delay_ms(10);

    // Peripheral initialization
    button.init();
    spi_io.init();
    spi_io.portMode(GPIO_OUTPUT);
    eeprom.init();
    eeprom.setWriteProtect();
    segments.init();
    rtc.begin();
    setSyncProvider(getTime);

    // Apply time and date from compiler
    if (extractDate(__DATE__))
    {
        if (extractTime(__TIME__))
        {
            rtc.write(tm);
        }
    }

    HAL::delay_ms(10);

    // Set RTC synchronization
    setSyncProvider(getTime);

    // OLED display initialization
    if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_SCREEN_ADDRESS))
    {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;);
    }

    display.clearDisplay();
    display.setTextSize(1);              // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE); // Draw white text
    display.setCursor(0, 0);             // Start at top-left corner
    display.cp437(true);                 // Use full 256 char 'Code Page 437' font

    display.print("Hello world!");
    display.display();

    HAL::delay_ms(10);

    // Read EEPROM contents into memory
    eeprom.read(0, data, 255);

    // Timer initialization
    timer.init(TIMER_PERIOD_US);
    timer.attachInterrupt(timerISR);
    timer.start();

    // Non-terminating loop
    while (true) 
    {
        static uint16_t val = 0;

        // Suspend timer when reading RTC due to shared bus
        timer.stop();
        previous_time = current_time;
        current_time  = now();
        timer.start();

        // Update measurements each second
        // Suspend timer during sensor read due to shared bus
        if (current_time != previous_time)
        {
            timer.stop();
            sensor.measure();
            timer.start();
            delay(20);
        }
        else
        {
            delay(80);
        }

        led.on();

        // Display loop count on 7-seg display and LED array
        spi_io.write((uint8_t)val);
        segments.write(val);

        if (current_time != previous_time)
        {
            display.fillRect(0, 8, 128, 24, SSD1306_BLACK);

            // Display current time on OLED
            display.setCursor(0, 8);
            printDate(current_time);
            display.print(' ');
            printTime(current_time);

            // Display sensor values on OLED
            display.setCursor(0, 16);
            display.printf("T: %05.2f'C H: %05.2f%%", sensor.getTemperature(), sensor.getHumidity());

            // Display button state on OLED
            display.setCursor(0, 24);
            display.print("Button ");

            if (button.released())
            {
                button.clearState();
                display.print("released.");
            }
            else if (button.pressed() || button.getState())
            {
                button.clearState();
                display.print("pressed.");
            }
            else
            {
                display.print("inactive.");
            }

            // Suspend timer when updating display due to shared bus
            timer.stop();
            display.display();
            timer.start();
        }
        else
        {
            delay(20);
        }

        led.off();

        ++val;

        // Write loop count to serial
        // On the Xiao hardware, timer conflict necessitates halting timer for printf()
        // timer.stop();
        // serial_bus.printf("Testing serial... Value = %d.\r\n", val);
        // timer.start();

        // Yield to framework USB background task
        yield();
        if (serialEventRun)
        {
            serialEventRun();
        }
    }

    return 0;
}

bool extractTime(const char *str)
{
  int Hour, Min, Sec;

  if (sscanf(str, "%d:%d:%d", &Hour, &Min, &Sec) != 3) return false;
  tm.Hour = Hour;
  tm.Minute = Min;
  tm.Second = Sec;
  return true;
}

bool extractDate(const char *str)
{
  char Month[12];
  int Day, Year;
  uint8_t monthIndex;

  if (sscanf(str, "%s %d %d", Month, &Day, &Year) != 3) return false;
  for (monthIndex = 0; monthIndex < 12; monthIndex++) {
    if (strcmp(Month, monthName[monthIndex]) == 0) break;
  }
  if (monthIndex >= 12) return false;
  tm.Day = Day;
  tm.Month = monthIndex + 1;
  tm.Year = CalendarYrToTm(Year);
  return true;
}

// Print an integer in "00" format (with leading zero),
// followed by a delimiter character
void printInteger(int val, char delim)
{
    if (val < 10)
        display.print("0");

    display.print((int)val);

    if (delim > 0)
        display.print(delim);

    return;
}

void printDate(time_t t)
{
    printInteger(day(t), 0);
    display.print('-');
    display.print(monthShortStr(month(t)));
    display.print('-');
    display.print((int)(year(t)));
}

void printTime(time_t t)
{
    printInteger(hour(t), ':');
    printInteger(minute(t), ':');
    printInteger(second(t), ' ');
}

time_t getTime()
{
    return rtc.get();
}

void timerISR()
{
    static bool update_button = false;

    segments.refresh();

    if (update_button)
    {
        button.poll();
    }

    update_button = !update_button;
}

// EOF
