//=============================================================
// File:    M5_LCD_Shapes.ino
//
// Author:  J. Hathway 2024
//
// Dependencies:
//     - M5StickCPlus library (M5Stack)
//
// Description:
//     - This is a reference sketch for using the M5.Lcd 
//       methods to print shapes to the built-in LCD display.
//=============================================================

#include <M5StickCPlus.h>

void setup() {
  // Initialise  M5Stick pins for LCD
  M5.begin();

  // Fill Screen
  M5.Lcd.fillScreen(WHITE);

  // Individual Pixels
  M5.Lcd.drawPixel(130, 240, YELLOW);  // x, y, colour

  // Line
  M5.Lcd.drawLine(30, 200, 130, 200, BLACK);  // x1, y1, x2, y2, colour

  // Rectangles
  // x, y, width, height, colour
  M5.Lcd.drawRect(0, 0, 67, 67, CYAN);
  //M5.Lcd.fillRect(67, 0, 68, 68, MAROON);

  // x, y, width, height, corner radius, colour
  M5.Lcd.fillRoundRect(67, 68, 68, 68, 8, GREEN);
  //M5.Lcd.drawRoundRect(0, 68, 67, 67, 4, ORANGE);

  // Circle
  // x0, y0, radius, colour
  M5.Lcd.fillCircle(50, 180, 50, BLUE);
  //M5.Lcd.drawCircle(67, 67, 50, YELLOW);

  // Triangle
  // x1, y1, x2, y2, x3, y3, colour
  M5.Lcd.drawTriangle(22, 22, 69, 98, 51, 22, RED);
  //M5.Lcd.fillTriangle(100, 100, 100, 0, 135, 0, NAVY);
}

void loop() {}