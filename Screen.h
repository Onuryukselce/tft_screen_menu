#ifndef SCREEN_H
#define SCREEN_H

#include "Canvas.h" // Canvas library

#include <stdint.h> // Library for uint16_t
#include <list> // Library for linked list
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735

class Screen {
  private:
  Canvas current;
  std::list <Canvas*> canvasList; 
  Adafruit_ST7735* tft;

  public:
  void drawLine(int x0, int y0, int x1, int y1,uint16_t color, int rotation);
  void draw();
  
};


#endif
