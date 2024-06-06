//=============================================================
// File:    BasicOSCSend.ino
//
// Author:  J. Hathway 2024
//
// Dependencies:
//     - M5StickCPlus library (M5Stack)
//     - OSC library (Adrian Freed)
//
// Description:
//     - Basic OSC messages send
//     - Send a simple OSC message with address "/test"
//=============================================================

#include <M5StickCPlus.h>

#include <WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>

//=============================================
//*********************************************
// **CHANGE THESE VARIABLES**
const char *ssid = "NetworkName";          // <----- your WiFi network's name (as appears on your phone/laptop)
const char *password = "NetworkPassword";  // <----- your WiFi password

const IPAddress outIp(192, 168, 23, 123);  // <----- IP address of receiving device
const unsigned int outPort = 8000;         // <----- Network port you are sending to
                                           //        **Must match inPort on receiving device
//*********************************************
//=============================================

// Function declarations
bool connectToWiFi();

// Object for OSC/UDP
WiFiUDP udp;

// Network port for incoming messages
const unsigned int localPort = 8000;  // This is not strictly needed for sending messages

//=============================================================
// SETUP
void setup() {
  // Initialize M5Stick
  M5.begin();

  // Initialize WiFi/UDP
  while (!connectToWiFi()) {}
  udp.begin(localPort);

  // Print network data to LCD
  M5.Lcd.println("Ready\n");
  M5.Lcd.println("Sending to:");
  M5.Lcd.print("IP: ");
  M5.Lcd.println(outIp);
  M5.Lcd.print("Port: ");
  M5.Lcd.println(outPort);
}

//=============================================================
// LOOP
void loop() {
  // 1. Create message
  OSCMessage msg("/test");  // a. message address
  msg.add(1);               // b. message body

  // 2. UDP packet
  udp.beginPacket(outIp, outPort);  // a. create packet
  msg.send(udp);                    // b. send packet
  udp.endPacket();                  // c. end packet

  // 3. Clear message before starting again
  msg.empty();

  // Add a short pause (e.g. 50 milliseconds) between cycles
  // This helps the WiFi router keep up
  delay(50);
}

//=============================================================
/// Connect to WiFi
/// - Function for connecting to WiFi network
/// @return status (bool) true = successful, false = failed
bool connectToWiFi() {
  M5.Lcd.print("Connecting");

  // initialise - WIFI_STA = Station Mode
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

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
    M5.Lcd.println(WiFi.localIP());

    delay(2000);
    return true;
  }
}