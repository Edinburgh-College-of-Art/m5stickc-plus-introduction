//=============================================================
// File:    M5_Buttons_IsHeld.ino
//
// Author:  J. Hathway 2024
//
// Dependencies:
//     - M5StickCPlus library (M5Stack)
//
// Description:
//     - This sketch will use the M5.BtnA.pressedFor() and 
//       M5.BtnB.pressedFor() methods to determine whether the 
//       HOME and RST buttons have been pressed for 2 seconds.
//
//     - This will then be printed to the LCD display on the 
//       M5StickC Plus board.
//=============================================================

#include <M5StickCPlus.h>
  
void setup() {
  M5.begin();
  M5.Lcd.setTextSize(2);
  M5.Lcd.println("Hold Btn:");
}
  
void loop() {
  // Check button status
  M5.update();
  
  // If HOME button is pressed for more than 2000ms
  if (M5.BtnA.pressedFor(2000)) {
    M5.Lcd.println("HOME Held"); // Print to LCD
    delay(1000);
  }
    
  // If RST button is pressed for more than 2000ms
  if (M5.BtnB.pressedFor(2000)) {
    M5.Lcd.println("RST Held"); // Print to LCD
    delay(1000);
  }
}