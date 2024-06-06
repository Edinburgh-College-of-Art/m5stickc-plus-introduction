//=============================================================
// File:    M5_Buzzer_Beep.ino
//
// Author:  J. Hathway 2024
//
// Dependencies:
//     - M5StickCPlus library (M5Stack)
//
// Description:
//     - This sketch will cause the built-in buzzer on the 
//       M5StickC Plus board to **beep** once every second.
//=============================================================

#include <M5StickCPlus.h>
  
void setup() {
  // Initialise M5Stick pins
  M5.begin();
}
  
void loop() {
  // Start 440Hz tone for 200ms
  M5.Beep.tone(440);
  delay(200);
  
  // Stop tone for 800ms
  M5.Beep.mute();
  delay(800);
}