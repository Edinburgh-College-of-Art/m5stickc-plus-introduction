//=============================================================
// File:    M5_LCD_Text.ino
//
// Author:  J. Hathway 2024
//
// Dependencies:
//     - M5StickCPlus library (M5Stack)
//
// Description:
//     - This is a reference sketch for using the M5.Lcd 
//       methods to print text to the built-in LCD display.
//=============================================================

#include <M5StickCPlus.h>
  
void setup() {
  // Initialise  M5Stick pins for LCD
  M5.begin();
  
  // Text Settings (optional)
  M5.Lcd.setRotation(1);       // screen rotation
  M5.Lcd.setTextSize(2);       // text size
  M5.Lcd.setTextColor(WHITE);  // text color
  
  // Starting position
  M5.Lcd.setCursor(0, 0);  // set text starting coordinates
  
  // Print to LCD
  M5.Lcd.print("Hello World");
  M5.Lcd.println("!!");
  M5.Lcd.printf("I am %s\nI am %i years old\n", "Joe", 25);
  M5.Lcd.printf("I am %f m tall", 3.1415);
}
  
void loop() {}