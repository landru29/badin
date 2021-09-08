# Badin

## Hardware

- STM32F103 (or eq CH32F103)
- Screen ILI9486 3.5inch 320x480 TFT-Shield

## Purpose

Display airspeed indicator. The file `airspeed.bmp` must be copied on the SD card of the TFT

## Pins

- SD card on SPI2:
   * SD_SS: `PB12`
   * SD_SCK: `PB13`
   * SD_DO: `PB14`
   * SD_DI: `PB15`
- TFT data on:
   * LCD_D0: `PA0`
   * LCD_D1: `PA1`
   * LCD_D2: `PA2`
   * LCD_D3: `PA3`
   * LCD_D4: `PA4`
   * LCD_D5: `PA5`
   * LCD_D6: `PA6`
   * LCD_D7: `PA7`
- TFT controls:
   * LCD_RD: `PB3`
   * LCD_WR: `PB4`
   * LCD_RS: `PB5`
   * LCD_CS: `PB6`
   * LCD_RST: `PB7`
- TFT supply:
   * 3V3: `3.3`
   * 5V: `5V`
   * GND: `G`