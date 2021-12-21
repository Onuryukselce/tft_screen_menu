#include "Canvas.h"

Canvas::Canvas() {
  // There is no matrix if doesnt defined
  row = column = 0;
  matrix = nullptr;
  bgcolor = ST77XX_WHITE;
}

Canvas::Canvas(int _row, int _column, uint16_t _bgcolor) {
  row = _row;
  column = _column;
  matrix = (uint16_t**) new uint16_t*[row];

// Allocate memory for each pointer
  for(int i = 0; i < row; i++) {
    matrix[i] = (uint16_t*)new uint16_t[column];
  }

  // Fill array matrix with bgcolor
  for(int i = 0;i < row; i++) {
    for(int j= 0; i < column; j++) {
      matrix[i][j] = bgcolor;
    }
  }
  
  
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