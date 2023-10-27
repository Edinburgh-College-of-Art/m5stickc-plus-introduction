//=============================================================
// File:    M5StickCPlus_WiFi.h
// 
// Author:  J. Hathway 2023
//
// Dependencies:
//     - M5StickCPlus library (M5Stack)
//
// Description:
//     - Functions for using WiFi with M5StickC Plus boards.
//     - connectToWifi() to connect to existing network.
//     - startWifiAP() to create a WiFi access point.
//=============================================================

#ifndef M5STICKC_PLUS
#define M5STICKC_PLUS
#define PRINT(x) M5.Lcd.print(x); Serial.print(x);
#define PRINT_LN(x) M5.Lcd.println(x); Serial.println(x);
#endif

#include <WiFi.h>

WiFiClient client;

//============================================================================
// CONNECT TO EXISTING NETWORK

/// Function for connecting to WiFi
/// @param _networkName (const char*) name of network
/// @param _password (const char*) network password
/// @param _timeout (int) optional - time spent attempting to access network
/// @return status (bool) true if successful, false if unsuccessful
bool connectToWifi(const char* _networkName, const char* _password, int _timeout = 20000) {
  PRINT("Connecting")

  // initialise - WIFI_STA = Station Mode
  WiFi.mode(WIFI_STA);
  WiFi.begin(_networkName, _password);

  // start timer
  unsigned long _startAttemptTime = millis();

  // while not connected to WiFi AND before timeout
  while (WiFi.status() != WL_CONNECTED && millis() - _startAttemptTime < _timeout) {
    PRINT(".")
    delay(400);
  }

  // Print status to LCD
  if (WiFi.status() != WL_CONNECTED) {
    PRINT_LN("\nErr: Failed to connect")
    delay(2000);
    return false;
  }
  else {
    PRINT_LN("\nConnected to:")
    PRINT_LN(_networkName)
    delay(2000);
    return true;
  }
}

//============================================================================
// CREATE ACCESS POINT MODE

/// Function for creating a WiFi Access Point
/// @param _networkName (const char*) name of network
/// @param _password (const char*) network password
/// @return status (bool) true if successful, false if unsuccessful
bool startWifiAP(const char* _networkName, const char* _password) {
  PRINT_LN("Starting WiFi AP: ")
  PRINT_LN(_networkName)

  // initialise - WIFI_AP = Access Point Mode 
  WiFi.mode(WIFI_AP);
  
  // start access point
  if (!WiFi.softAP(_networkName, _password)) {
    PRINT_LN("Err: Access Point Failed");
    delay(2000);
    return false;
  }
  
  // print IP Address
  PRINT_LN("Access Point Created");
  PRINT_LN("AP IP Address:")
  PRINT_LN(WiFi.softAPIP())
  delay(2000);

  return true;
}