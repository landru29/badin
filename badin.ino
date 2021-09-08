/*
 * 8bit TFT Library for STM32F103
 * based on MCUFRIEND_kbv.cpp by David Prentice
 * https://github.com/prenticedavid/MCUFRIEND_kbv
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <Adafruit_GFX.h>
#include "STM32_TFT_8bit.h"
#include <SdFat.h>        // https://github.com/greiman/SdFat
#include "image.h"
#include "indicator.h"

#define SD_CS PB12   // chip select for sd2

static SPIClass mySPI2(2);
// Chip select PB12, dedicated SPI, 18 MHz, port 2.


#define SD2_CONFIG SdSpiConfig(PB12, DEDICATED_SPI, SD_SCK_MHZ(18), &mySPI2)


SdFs sd2;


#define TFT_BLACK       0x0000      /*   0,   0,   0 */
#define TFT_NAVY        0x000F      /*   0,   0, 128 */
#define TFT_DARKGREEN   0x03E0      /*   0, 128,   0 */
#define TFT_DARKCYAN    0x03EF      /*   0, 128, 128 */
#define TFT_MAROON      0x7800      /* 128,   0,   0 */
#define TFT_PURPLE      0x780F      /* 128,   0, 128 */
#define TFT_OLIVE       0x7BE0      /* 128, 128,   0 */
#define TFT_LIGHTGREY   0xC618      /* 192, 192, 192 */
#define TFT_DARKGREY    0x7BEF      /* 128, 128, 128 */
#define TFT_BLUE        0x001F      /*   0,   0, 255 */
#define TFT_GREEN       0x07E0      /*   0, 255,   0 */
#define TFT_CYAN        0x07FF      /*   0, 255, 255 */
#define TFT_RED         0xF800      /* 255,   0,   0 */
#define TFT_MAGENTA     0xF81F      /* 255,   0, 255 */
#define TFT_YELLOW      0xFFE0      /* 255, 255,   0 */
#define TFT_WHITE       0xFFFF      /* 255, 255, 255 */
#define TFT_ORANGE      0xFDA0      /* 255, 180,   0 */
#define TFT_GREENYELLOW 0xB7E0      /* 180, 255,   0 */
#define TFT_PINK        0xFC9F


STM32_TFT_8bit tft;

// Use second SPI port
/*
 * MOSI --- PB15
 * MISO --- PB14
 * SCK ---- PB13 
 * CS ----- PB12
 */

Image *img;
Indicator *ind;

void setup()
{
    uint16_t ID;
    Serial.begin(9600);
    Serial.print("Show BMP files on TFT with ID:0x");
    ID = tft.readID();
    Serial.println(ID, HEX);
    tft.setResolution(320, 480); // Set your resolution
    tft.begin(ID);
    //tft.fillScreen(0x001F);
    tft.setTextColor(0xFFFF, 0x0000);
    bool good = sd2.begin(SD2_CONFIG);
    if (!good) {
        Serial.print(F("cannot start SD"));
        while (1);
    }

    img = new Image(&tft, &sd2);
    ind = new Indicator(&tft);
}


void loop()
{
    uint8_t ret;
    uint32_t start;
    tft.fillScreen(0);
    start = millis();
    ret = img->showBMP("/airspeed.bmp", 5, 5);
    switch (ret) {
        case 0:
            Serial.print(millis() - start);
            Serial.println(F("ms"));
            break;
        case 1:
            Serial.println(F("bad position"));
            break;
        case 2:
            Serial.println(F("bad BMP ID"));
            break;
        case 3:
            Serial.println(F("wrong number of planes"));
            break;
        case 4:
            Serial.println(F("unsupported BMP format"));
            break;
        case 5:
            Serial.println(F("unsupported palette"));
            break;
        default:
            Serial.println(F("unknown"));
        break;
    }

    ind->setSpeed(75);
    
    while(true) {}
}
