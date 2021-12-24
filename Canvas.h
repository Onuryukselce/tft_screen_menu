#ifndef CANVAS_H
#define CANVAS_H

// Some ready-made 16-bit ('565') color settings:
#define ST77XX_BLACK 0x0000
#define ST77XX_WHITE 0xFFFF
#define ST77XX_RED 0xF800
#define ST77XX_GREEN 0x07E0
#define ST77XX_BLUE 0x001F
#define ST77XX_CYAN 0x07FF
#define ST77XX_MAGENTA 0xF81F
#define ST77XX_YELLOW 0xFFE0
#define ST77XX_ORANGE 0xFC00

#include <stdint.h> // Library for int16_t
#include <Arduino.h>

class Canvas {
  private:
  uint16_t** matrix;
  uint16_t bgcolor;
  
  
  public:
  int row;
  int column;
  Canvas();
  Canvas(int _row, int _column, uint16_t _bgcolor);
  Canvas(const Canvas& _Canvas);
  uint16_t getPixel(int i, int j);
  void setPixel(int i, int  j, uint16_t color);
  void writeFastHLine(int16_t x, int16_t y ,int16_t w, uint16_t color);
  void writeFastVLine(int16_t x, int16_t y, int16_t w, uint16_t color);
  void writeLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color, int rotation);
  void writeRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
  void writeCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
  //operator overloading
  Canvas operator=(const Canvas& _Canvas);
  };

#endif
