#ifndef __IMAGE_H__
#define __IMAGE_H__

#define BUFFPIXEL      20
#define PALETTEDEPTH   0     // do not support Palette modes

#include "STM32_TFT_8bit.h"
#include <Arduino.h>
#include <SdFat.h>        // https://github.com/greiman/SdFat


class Image {
  public:
    Image(STM32_TFT_8bit* tft, SdFat* sd);
    uint8_t showBMP(char *nm, int x, int y);
    
  private:
    STM32_TFT_8bit* tft;
    SdFat* sd;

    uint16_t read16(File& f);
    uint32_t read32(File& f);

};



#endif
