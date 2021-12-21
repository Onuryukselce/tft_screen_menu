#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <SPI.h>

class Screen : public Adafruit_ST7735 {
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
      String msg = "pos:";
      msg+= x;
      msg+=",";
      msg+= y;
      Serial.println(msg);
  
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
