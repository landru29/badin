#include "indicator.h"

Indicator::Indicator(STM32_TFT_8bit* tft) {
  this->tft = tft;
  this->xOffset=159;
  this->yOffset=159;
}

void Indicator::setSpeed(float value) {
  float angle = 0.0335*value-0.73;
  if (value>160) {
    angle = 0.030*value-0.59;
  }
  this->tft->drawLine(
    this->xOffset,
    this->yOffset,
    this->xOffset+80*sin(angle), 
    this->yOffset-80*cos(angle),
    0xFFFF
  );
}
