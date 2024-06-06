//==============================================================
// File:    M5_ESPNOW_Send.ino
//
// Author:  J. Hathway 2024
//
// Dependencies:
//     - M5StickCPlus library (M5Stack)
//
// Description:
//     - This sketch will send ESP-NOW messages to specified
//       MAC addresses.
//
//     - You will need to enter the MAC address of the device(s)
//       you wish to send to.
//==============================================================

#include <M5StickCPlus.h>
#include <WiFi.h>
#include <esp_now.h>
  
// Message to send
String outgoingMsg = "Hello World!";
  
// ESP-NOW variables
esp_now_peer_info_t peerInfo;
int peerCount = 0;
  
// Function declarations
void sendTo(uint8_t *address);
void callbackFunction(const uint8_t *_mac_addr, esp_now_send_status_t _status);
  
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
  
  // callbackFunction() executed when message is sent
  esp_now_register_send_cb(callbackFunction);
  
  // register peer
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  
  // MAC address(es) to send to
  uint8_t macAddress[] = { 0x4C, 0x75, 0x25, 0x9E, 0x9F, 0xF4 };
  //uint8_t macAddress2[] = { 0x4C, 0x75, 0x25, 0x9F, 0x09, 0x28 };
  
  // pair with MAC address(es)
  sendTo(macAddress);
  //sendTo(macAddress2);
}
  
//==============================================
// LOOP
void loop() {
  // Send ESP-NOW message
  esp_err_t result = esp_now_send(0, (uint8_t *)&outgoingMsg, sizeof(outgoingMsg));
  
  // Check if message was sent successfully
  if (result != ESP_OK) {
    M5.Lcd.println("Error: Message not sent.");
  }
    
  // Wait 10 seconds before trying again
  delay(10000);
}
    
//==============================================
// Pair a device
void sendTo(uint8_t *address) {
  peerCount++;
  
  // register peer
  memcpy(peerInfo.peer_addr, address, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    M5.Lcd.println("Error: Failed to add peer " + String(peerCount));
  }
}
  
//==============================================
// Function to be executed when ESP-NOW message is sent
void callbackFunction(const uint8_t *_mac_addr, esp_now_send_status_t _status) {
  // Clear display
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
  
  M5.Lcd.println("Sending message:");
  M5.Lcd.println(outgoingMsg);
  
  // Check if message was delivered
  if (_status != ESP_NOW_SEND_SUCCESS) {
    M5.Lcd.println("Error: Failed to deliver.");
  } else {
    M5.Lcd.println("Delivered.");
  }
}