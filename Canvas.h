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

#include <stdint.h> // Library for uint16_t
 
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
