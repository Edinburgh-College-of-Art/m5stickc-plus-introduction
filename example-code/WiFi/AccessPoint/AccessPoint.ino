//=======================================================
// File:    AccessPoint.ino
//
// Author:  J. Hathway 2024
//
// Dependencies:
//     - M5StickCPlus Library (M5Stack).
//     - WiFi Library (Arduino).
//
// Description:
//     - Demo of how to use M5StickC-Plus as
//       an Access Point (AP)
//=======================================================

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

    // Start Access Point
    startWifiAP(ssid, password);
}

void loop() {}

// Start Access Point Function
bool startWifiAP(const char* ssid, const char* pass) {
  M5.Lcd.println("Starting WiFi AP: ");
  M5.Lcd.println(networkName);

  // initialise - WIFI_AP = Access Point Mode 
  WiFi.mode(WIFI_AP);
  
  // start access point
  if (!WiFi.softAP(networkName, pass)) {
    M5.Lcd.println("Err: Access Point Failed");
    delay(2000);
    return false;
  }
  
  // print IP Address
  M5.Lcd.println("Access Point Created");
  M5.Lcd.println("AP IP Address:");
  M5.Lcd.println(WiFi.softAPIP());
  delay(2000);

  return true;
}