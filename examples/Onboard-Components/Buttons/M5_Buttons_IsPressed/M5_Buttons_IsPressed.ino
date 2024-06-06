//=============================================================
// File:    M5_Buttons_IsPressed.ino
//
// Author:  J. Hathway 2024
//
// Dependencies:
//     - M5StickCPlus library (M5Stack)
//
// Description:
//     - This sketch will use the M5.BtnA.isPressed() method 
//       to determine whether the HOME button is pressed.
//
//     - This will then be printed to the LCD display on the 
//       M5StickC Plus board.
//=============================================================

#include <M5StickCPlus.h>
  
void setup() {
  M5.begin();
  M5.Lcd.setTextSize(3);
}
  
void loop() {
  // Check button status
  M5.update(); 
    
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.println("HOME:");
  
  // Check if HOME button is pressed
  if (M5.BtnA.isPressed()) {   
    M5.Lcd.println("Press  ");
  }
  else{
    M5.Lcd.println("Release");
  }
}