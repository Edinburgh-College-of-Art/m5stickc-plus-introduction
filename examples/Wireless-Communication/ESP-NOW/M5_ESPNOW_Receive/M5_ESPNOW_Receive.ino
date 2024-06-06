//=============================================================
// File:    M5_ESPNOW_Receive.ino
//
// Author:  J. Hathway 2024
//
// Dependencies:
//     - M5StickCPlus library (M5Stack)
//
// Description:
//     - This sketch will receive any incoming ESP-NOW
//       messages and print them to the LCD display.
//=============================================================

#include <M5StickCPlus.h>
#include <WiFi.h>
#include <esp_now.h>
  
// Variable to store received messages
String incomingMsg = "";
  
// Function declarations
void callbackFunction(const uint8_t *_mac_addr, const uint8_t *_incomingData, int _len);
  
//==============================================
// SETUP
void setup() {
  // Initialise M5Stick
  M5.begin();
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  
  // Initialise ESPNOW
  // Do not continue if not initialised
  if (esp_now_init() != ESP_OK) {
    M5.Lcd.println("Error initializing ESP-NOW");
    while (true) {}
  }
  
  // callbackFunction() called when receive is received
  esp_now_register_recv_cb(callbackFunction);
}
  
//==============================================
// LOOP
void loop() {}
  
//==============================================
// Function is executed when message is received
void callbackFunction(const uint8_t *_mac_addr, const uint8_t *_incomingData, int _len) {
  // Clear string variable
  incomingMsg = "";
  
  // Copy incoming data to message variable
  for (int i = 0; i < _len; i++) {
    // If end of strink, break loop
    if ((char)_incomingData[i] == '\0') {
      break;
    }
  
    incomingMsg += (char)_incomingData[i];
  }
  
  // Print message to LCD display
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.printf("New Msg:\n%s", incomingMsg);
}