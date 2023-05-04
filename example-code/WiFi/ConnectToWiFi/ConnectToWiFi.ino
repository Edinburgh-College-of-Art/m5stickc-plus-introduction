//=======================================================
// File:    ConnectToWiFi.ino
//
// Author:  J. Hathway 2024
//
// Dependencies:
//     - M5StickCPlus Library (M5Stack).
//     - WiFi Library (Arduino).
//
// Description:
//     - Demo of how to connect M5StickC-Plus to WiFi.
//=======================================================

#include <M5StickCPlus.h>
#include <WiFi.h>

//=======================================================
// **REPLACE THESE VARIABLES WITH YOUR DETAILS**
const char *ssid = "MyNetwork";
const char *password = "MyPassword";
//=======================================================

bool connectToWiFi(const char* ssid, const char* pass);

void setup()
{
    M5.begin();
    
    // Connect to WiFi
    connectToWiFi(ssid, password);
}

void loop() {}

// Connect to WiFi Function
bool connectToWiFi(const char* ssid, const char* pass) {
  M5.Lcd.print("Connecting");

  // initialise - WIFI_STA = Station Mode
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  // start timer
  unsigned long startAttemptTime = millis();

  // while not connected to WiFi AND before timeout
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 30000) {
    M5.Lcd.print(".");
    delay(400);
  }

  // Print status to LCD
  if (WiFi.status() != WL_CONNECTED) {
    M5.Lcd.println("\nErr: Failed to connect");
    delay(2000);
    return false;
  } else {
    M5.Lcd.println("\nConnected to:");
    M5.Lcd.println(ssid);
    delay(2000);
    return true;
  }
}