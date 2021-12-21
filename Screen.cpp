#include "Screen.h"

void Screen::draw() {
  for(int i=0; i < tft->width(); i++) {
    for(int j = 0; j < tft->height(); j++) {
      tft->writePixel(i,j, current.getPixel(i,j));
    }
   }
}

void Screen::drawLine(int x0, int y0, int x1, int y1, uint16_t color, int rotation) {
  
  // Bresenham's line drawing
  if (rotation == 0) {
    int m_new = 2 * (y1 - y0);
    int slope_error_new = m_new - (x1 - x0);
    
    for(int x = x0, y = y0; x <= x1; x++) {
      current.setPixel(x,y,color);
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
