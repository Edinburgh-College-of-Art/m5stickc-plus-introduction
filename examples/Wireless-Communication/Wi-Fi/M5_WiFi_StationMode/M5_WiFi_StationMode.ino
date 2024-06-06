//=============================================================
// File:    M5_WiFi_StationMode.ino
//
// Author:  J. Hathway 2024
//
// Dependencies:
//     - M5StickCPlus library (M5Stack)
//
// Description:
//     - This sketch will connect the M5StickC Plus
//       board to a specified Wi-Fi network.
//
//     - You will need to replace the ssid and password
//       variables with your own Wi-Fi network name and
//       password.
//=============================================================

#include <M5StickCPlus.h>
#include <WiFi.h>
  
//=======================================================
// **REPLACE THESE VARIABLES WITH YOUR DETAILS**
const char *ssid = "MyNetwork";
const char *password = "MyPassword";
//=======================================================
  
void setup() {
  M5.begin();
  M5.Lcd.print("Connecting");
  
  // initialise - WIFI_STA = Station Mode
  WiFi.mode(WIFI_STA);
  
  // Start connection
  WiFi.begin(ssid, password);
  
  // Wait until connected
  while (WiFi.status() != WL_CONNECTED) {
    M5.Lcd.print(".");
    delay(400);
  }
  
  M5.Lcd.print("Connected");
}
  
void loop() {}