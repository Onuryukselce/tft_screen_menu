#include <Arduino.h>
#include "Screen.h"

#define SCLK 22
#define MOSI 21
#define CS   4
#define DC   32
#define RESET 33

Adafruit_ST7735 tft = Adafruit_ST7735(CS, DC, MOSI, SCLK, RESET);
Canvas conv(128,128, ST77XX_BLACK);

void setup() {
  Serial.println("DENEMe");
  tft.initR(INITR_144GREENTAB);
  tft.fillScreen(ST77XX_BLACK);
  Screen test;
  test.tft = &tft;
  test.currentCanvas = conv,
  Serial.println("matrix atandı!");
  //test.currentCanvas = conv;
  //test.drawFastHLine(0,0,128);
  //test.drawFastVLine(0,0,128);
  Serial.println("tft atandı!");
  test.drawCanvasRect(0,0,128,128);
  test.currentCanvas.writeCircle(64,64,10,ST77XX_GREEN);
  test.currentCanvas.writeCircle(64,64,11,ST77XX_MAGENTA);
  test.currentCanvas.writeCircle(64,64,12,ST77XX_RED);
  test.drawCanvasRect(51,51,76,76);

    Serial.println("circle!");

  //test.drawCanvasRect(0,0, 128, 128);
  //test.tft->fillRect(0,0,128,128, ST77XX_GREEN);
    printCanvas(test.currentCanvas);
}

void loop() {
  // put your main code here, to run repeatedly:
  
}

void printCanvas(Canvas &canvas) {
  for(int i = 0; i < canvas.row; i++) {
    for(int j = 0; j < canvas.column; j++) {
      Serial.print(canvas.getPixel(i,j), HEX);
    }
    Serial.println("");
  }
}
