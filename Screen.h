#ifndef SCREEN_H
#define SCREEN_H

#include "Canvas.h" // Canvas library

#include <stdint.h> // Library for uint16_t
#include <list> // Library for linked list
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735

class Screen {
  private:
  std::list <Canvas*> canvasList; 

  public:
  Screen();
  Canvas currentCanvas;
  Screen(Adafruit_ST7735 _tft);
  Adafruit_ST7735* tft;
  void drawFastHLine(int16_t x, int16_t y ,int16_t w);
  void drawFastVLine(int16_t x, int16_t y, int16_t w);
  void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int rotation);
  void drawCanvasRect(int16_t x, int16_t y, int16_t w, int16_t h);
  void draw();
  
};


#endif
