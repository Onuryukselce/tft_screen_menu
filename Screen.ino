#include "Screen.h"
#include "Canvas.h"

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
