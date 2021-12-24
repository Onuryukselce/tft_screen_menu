#include "Screen.h"

#ifndef _swap_int16_t
#define _swap_int16_t(a, b)                                                    \
  {                                                                            \
    int16_t t = a;                                                             \
    a = b;                                                                     \
    b = t;                                                                     \
  }
#endif

Screen::Screen() {
 // Canvas conv(128, 128, ST77XX_BLACK);
  // currentCanvas = conv;
}

Screen::Screen(Adafruit_ST7735 _tft) {
  tft = &_tft;
  //Canvas conv(tft->width(), tft->height(), ST77XX_BLACK);
  //currentCanvas = conv;
}

void Screen::drawFastHLine(int16_t x, int16_t y, int16_t w) {
  drawLine(x,y,x+w-1,y,0);
}

void Screen::drawFastVLine(int16_t x, int16_t y, int16_t h) {
  drawLine(x, y, x, y + h - 1 ,0);
}

void Screen::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int rotation) {
  
  // Bresenham's line drawing
  #if defined(ESP8266)
  yield();
  #endif
  if (rotation == 0) {    

    int16_t steep = abs(y1-y0) > abs(x1-x0);

    if (steep) {
      _swap_int16_t(x0,y0);
      _swap_int16_t(x1,y1);
    }

    if (x0 > x1) {
    _swap_int16_t(x0, x1);
    _swap_int16_t(y0, y1);
    }

  int16_t dx, dy;
  dx = x1 - x0;
  dy = abs(y1 - y0);

  int16_t err = dx / 2;
  int16_t ystep;

  if (y0 < y1) {
    ystep = 1;
  } else {
    ystep = -1;
  }

  for (; x0 <= x1; x0++) {
    /* Serial.print("coord(x,y) => ");
     Serial.print("(");
     Serial.print(x);
    Serial.print(",");
     Serial.print(y);
   Serial.println(")");*/

      if(steep)
      tft->drawPixel(y0,x0, currentCanvas.getPixel(x0,y0));
      else
      tft->drawPixel(x0,y0, currentCanvas.getPixel(x0,y0));
        
      err -= dy;
    if (err < 0) {
      y0 += ystep;
      err += dx;
    }
    } 
  }
}

void Screen::drawCanvasRect(int16_t x, int16_t y, int16_t w, int16_t h) {
  for(int16_t i = x; i < x + w; i++) {
    drawFastVLine(i,y,h);
  }
}
