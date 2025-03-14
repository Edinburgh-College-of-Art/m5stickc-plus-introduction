//=============================================================
// File:    M5_WiFi_AccessPoint.ino
//
// Author:  J. Hathway 2024
//
// Dependencies:
//     - M5StickCPlus library (M5Stack)
//
// Description:
//     - This sketch will create a Wi-Fi access point from the 
//       M5StickC Plus. 
//
//     - It will allow other devices to join the
//       same network in order to communicate with each other.
//
//     - This does NOT provide a connection to the internet.
//=============================================================

#include <M5StickCPlus.h>
#include <WiFi.h>
   
//=======================================================
// **REPLACE THESE VARIABLES WITH YOUR DETAILS**
const char *ssid = "MyNetwork";      // You can choose what your access point is called
const char *password = "MyPassword"; // You can also set a password for your access point
//=======================================================
   
bool startWifiAP(const char* ssid, const char* pass);
   
void setup() {
  M5.begin();
  M5.Lcd.println("Starting WiFi AP: ");
  M5.Lcd.println(ssid);
  
  // initialise - WIFI_AP = Access Point Mode 
  WiFi.mode(WIFI_AP);
    
  // start access point
  while (!WiFi.softAP(ssid, password)) {
    M5.Lcd.println("Err: Access Point Failed");
    delay(2000);
  }
    
  // print IP Address
  M5.Lcd.println("Access Point Created");
  M5.Lcd.println("AP IP Address:");
  M5.Lcd.println(ssid);
  M5.Lcd.println(WiFi.softAPIP());
  delay(2000);
}
   
void loop() {}