#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h> // Library for uint16_t
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735

class Screen {
  private:
  uint16_t canvas[128][128];
  Screen *next;
  Screen *previous;
  
  
  public:
  Screen *getNext();
  Screen *getPrev();
  void drawLine(Adafruit_ST7735 tft, int x0, int y0, int x1, int y1,uint16_t color, int rotation);
  void draw(Adafruit_ST7735 tft);
  uint16_t *getCanvas(uint16_t canvas[128][128]);
};


#endif