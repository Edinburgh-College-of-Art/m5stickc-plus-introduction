//=============================================================
// File:    M5_LED_Blink.ino
//
// Author:  J. Hathway 2024
//
// Dependencies:
//     - M5StickCPlus library (M5Stack)
//
// Description:
//     - This sketch will cause the built-in LED on the 
//       M5StickC Plus board to **blink** once every second.
//=============================================================

#include <M5StickCPlus.h>
  
// Pin 10 is connected to the built-in LED
const int ledPin = 10;
  
void setup() {
  // initialise ledPin as an OUTPUT
  pinMode(ledPin, OUTPUT);
}
  
void loop() {
  // Turn on LED for 1 second
  digitalWrite(ledPin, HIGH);
  delay(1000);
  
  // Turn off LED for 1 second
  digitalWrite(ledPin, LOW);
  delay(1000);
}