#ifndef __INDICATOR__H__
#define __INDICATOR__H__

#include "STM32_TFT_8bit.h"
#include <Arduino.h>

class Indicator {
  public:
    Indicator(STM32_TFT_8bit* tft);
    void setSpeed(float value);
    
  private:
    STM32_TFT_8bit* tft;
    int xOffset;
    int yOffset;
};

#endif
