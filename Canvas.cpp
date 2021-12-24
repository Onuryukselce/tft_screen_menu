#include "Canvas.h"

#ifndef _swap_int16_t
#define _swap_int16_t(a, b)                                                    \
  {                                                                            \
    int16_t t = a;                                                             \
    a = b;                                                                     \
    b = t;                                                                     \
  }
#endif

Canvas::Canvas() {
  // There is no matrix if doesnt defined
  row = column = 0;
  matrix = nullptr;
  bgcolor = ST77XX_BLACK;
}

Canvas::Canvas(int _row, int _column, uint16_t _bgcolor) {
  Serial.begin(115200);
  row = _row;
  Serial.print("row:");
  Serial.println(row);
  column = _column;
  Serial.print("col:");
  Serial.println(column);
  matrix = (uint16_t**) new uint16_t*[row];

// Allocate memory for each pointer
  for(int i = 0; i < row; i++) {
    matrix[i] = (uint16_t*)new uint16_t[column];
  }

  // Fill array matrix with bgcolor
  for(int i = 0;i < row; i++) {
    for(int j= 0; j < column; j++) {
      matrix[i][j] = _bgcolor;
      delay(0);
    }
  delay(0);
  }

  Serial.println("Exit For");
  
  
}

Canvas::Canvas(const Canvas& _Canvas) {
  row = _Canvas.row;
  column = _Canvas.column;

  // MAtrix allocate memory
  matrix = (uint16_t**) new uint16_t*[row];

  for (int i =0; i < row; i++) {
    matrix[i] = (uint16_t*) new uint16_t[column];
  }

  //fill with matrix colors;
  for(int i =0; i < row; i++) {
    for (int j = 0; j < column; j++) {
      matrix[i][j] = _Canvas.matrix[i][j];
    }
  }
  
}

uint16_t Canvas::getPixel(int i, int j) {
  if((row > 0) && (column > 0)) {
    return matrix[i][j];
  }
  return 0;
}

void Canvas::setPixel(int i, int j, uint16_t color) {
  if ((i < 0) || (i >= row)) {
    return;
  }
  if((j < 0) || (j >= column)) {
    return;
  }
  matrix[i][j] = color;
}

// Operator overloading
Canvas Canvas::operator=(const Canvas& _Canvas) {
  if(column > 0) {
    // free memory previously allocated for the object *this
    for(int i = 0; i < row; i++) {
      delete[] matrix[i];
    }
  }
  if(row >0) {
    delete[] matrix;
  }

  // Copy
  row = _Canvas.row;
  column = _Canvas.column;

  // Allocate memory for matrix
  matrix = (uint16_t**) new uint16_t*[row];
  for(int i = 0; i < row; i++) {
    matrix[i] = (uint16_t*) new uint16_t[column];
  }

  //fill with matrix
  for(int i =0; i < row; i++) {
    for(int j = 0; j < row; j++) {
      matrix[i][j] = _Canvas.matrix[i][j];
    }
  }
}

void Canvas::writeFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
  writeLine(x,y,x+w-1,y,color,0);
}

void Canvas::writeFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
  writeLine(x, y, x, y + h - 1 ,color,0);
}

void Canvas::writeLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color, int rotation) {
  
  // Bresenham's line writeing
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
      setPixel(y0,x0, color);
      else
      setPixel(x0,y0, color);
        
      err -= dy;
    if (err < 0) {
      y0 += ystep;
      err += dx;
    }
    } 
  }
}

void Canvas::writeRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
  for(int16_t i = x; i < x + w; i++) {
    writeFastVLine(i,y,h,color);
  }
}

void Canvas::writeCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
  #if defined(ESP8266)
  yield();
#endif
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;

  setPixel(x0, y0 + r, color);
  setPixel(x0, y0 - r, color);
  setPixel(x0 + r, y0, color);
  setPixel(x0 - r, y0, color);

  while (x < y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;

    setPixel(x0 + x, y0 + y, color);
    setPixel(x0 - x, y0 + y, color);
    setPixel(x0 + x, y0 - y, color);
    setPixel(x0 - x, y0 - y, color);
    setPixel(x0 + y, y0 + x, color);
    setPixel(x0 - y, y0 + x, color);
    setPixel(x0 + y, y0 - x, color);
    setPixel(x0 - y, y0 - x, color);
  }

}
