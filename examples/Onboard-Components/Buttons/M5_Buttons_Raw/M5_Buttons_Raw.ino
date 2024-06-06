//=============================================================
// File:    M5_Buttons_Raw.ino
//
// Author:  J. Hathway 2024
//
// Dependencies:
//     - M5StickCPlus library (M5Stack)
//
// Description:
//     - This sketch will print the raw button values to the 
//       LCD display on the M5StickC Plus.
//=============================================================

#include <M5StickCPlus.h>
  
void setup() {
  M5.begin();
  M5.Lcd.setTextSize(3);
}
  
void loop() {
  // Read buttons
  int homeBtnValue = M5.BtnA.read();
  int rstBtnValue = M5.BtnB.read();
  
  // Print data
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.printf("HOME: %i\n", homeBtnValue);
  M5.Lcd.printf("RST: %i", rstBtnValue);
}