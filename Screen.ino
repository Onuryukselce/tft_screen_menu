#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <SPI.h>

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

uint16_t *Screen::getCanvas(uint16_t canvas[128][128]) {
  canvas = this->canvas;
}

Screen *Screen::getNext() {
  return this->next;
}

Screen *Screen::getPrev() {
  return this->previous;
}

void Screen::draw(Adafruit_ST7735 tft) {
  for(int i=0; i < tft.width(); i++) {
    for(int j = 0; j < tft.height(); j++) {
      tft.writePixel(i,j, this->canvas[i][j]);
    }
   }
}

void Screen::drawLine(Adafruit_ST7735 tft, int x0, int y0, int x1, int y1, uint16_t color, int rotation) {
  
  // Bresenham's line drawing
  if (rotation == 0) {
    int m_new = 2 * (y1 - y0);
    int slope_error_new = m_new - (x1 - x0);
    Serial.begin(115200);
    
    for(int x = x0, y = y0; x <= x1; x++) {
      tft.drawPixel(x,y, color);
      slope_error_new += m_new;
  
      // Slope error reached limit, time to
      // increment y and update slope error.
      if (slope_error_new >= 0)
      {
         y++;
         slope_error_new  -= 2 * (x1 - x0);
      }
    } 
  }
}


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


Canvas::Canvas() {
  // There is no matrix if doesnt defined
  row = column = 0;
  matrix = nullptr;
  bgcolor = ST7735_WHITE;
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

#define SCLK 22
#define MOSI 21
#define CS   4
#define DC   32
#define RESET 33

Adafruit_ST7735 tft = Adafruit_ST7735(CS, DC, MOSI, SCLK, RESET);
Screen test;



void setup() {
  tft.initR(INITR_144GREENTAB);
  tft.fillScreen(ST77XX_BLACK);
  test.drawLine(tft, 0, 0, 128,128, ST77XX_GREEN, 0);
}

void loop() {
  // put your main code here, to run repeatedly:

}
