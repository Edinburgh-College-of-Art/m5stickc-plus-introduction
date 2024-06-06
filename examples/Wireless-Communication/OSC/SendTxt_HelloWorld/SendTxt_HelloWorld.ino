//=============================================================
// File:    SendTxt_HelloWorld.ino
//
// Author:  J. Hathway 2024
//
// Dependencies:
//     - M5StickCPlus library (M5Stack)
//     - OSC library (Adrian Freed)
//
// Description:
//     - Send Hello World message via OSC
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

// Object for OSC/UDP
WiFiUDP udp;

// Network port for incoming messages
const unsigned int localPort = 8000; // This is not strictly needed for sending messages

//=============================================================
// FUNCTIONS

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

/// Send Text OSC Message
/// - function for sending text messages via OSC
/// @param address (const char*) message tag
/// @param message (String) message to send
void sendTextOscMessage(const char *address, const char *message) {
  // init message
  OSCMessage oscMsg(address);
  oscMsg.add(message);

  // send message
  udp.beginPacket(outIp, outPort);
  oscMsg.send(udp);

  // clear message
  udp.endPacket();
  oscMsg.empty();
}

//=============================================================
// SETUP
void setup() {
  M5.begin();

  // connect to network
  while (!connectToWiFi()) {}
  udp.begin(localPort);
}

//=============================================================
// LOOP
void loop() {
  // send OSC message
  sendTextOscMessage("/m5stick", "Hello World!");

  // perform the loop every 15 ms
  // this may be too fast for some routers to enjoy themselves
  // so set it to something less if you need to
  delay(27);
}