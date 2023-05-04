//=======================================================
// File:    ConnectWithHeaderFile.ino
//
// Author:  J. Hathway 2024
//
// Dependencies:
//     - M5StickCPlus Library (M5Stack).
//     - M5Stick_WiFi.h (J. Hathway).
//
// Description:
//     - Demo of how to use the M5Stick_WiFi Header File 
//       to connect to a WiFi network.
//=======================================================

#include <M5StickCPlus.h>
#include "M5Stick_WiFi.h" // include the header file in your sketch folder

//=======================================================
// **REPLACE THESE VARIABLES WITH YOUR DETAILS**
const char* ssid = "MyNetwork";
const char* password = "MyPassword";
//=======================================================

void setup() {
  M5.begin();

  // Use this function to connect
  connectToWifi(ssid, password);
}

void loop() { }