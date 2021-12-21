#ifndef CANVAS_H
#define CANVAS_H

#include <stdint.h> // Library for uint16_t
#include <Adafruit_ST77XX.h>    // Core graphics library

class Canvas {
  private:
  uint16_t** matrix;
  uint16_t bgcolor;
  int row;
  int column;
  
  public:
  Canvas();
  Canvas(int _row, int _column, uint16_t _bgcolor);
  Canvas(const Canvas& _Canvas);
  uint16_t getPixel(int i, int j);
  void setPixel(int i, int  j, uint16_t color);

  //operator overloading
  Canvas operator=(const Canvas& _Canvas);
  };

#endif