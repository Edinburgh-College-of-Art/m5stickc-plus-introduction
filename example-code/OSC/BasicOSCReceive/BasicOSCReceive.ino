//=============================================================
// File:    BasicOSCReceive.ino
//
// Author:  J. Hathway 2024
//
// Dependencies:
//     - M5StickCPlus library (M5Stack)
//     - OSC library (Adrian Freed)
//
// Description:
//     - Basic receive OSC messages
//     - Receive messages with address "/test"
//     - Print to LCD
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

const unsigned int inPort = 8000;  // <----- Network port to receive OSC messages
                                   //        **Must match outPort on sending device
//*********************************************
//=============================================

// Function declarations
bool connectToWiFi();

// Objects required for OSC/UDP
WiFiUDP udp;
OSCErrorCode error;

//=============================================================
/// routeTest - Callback function
/// - Is called when message with address "/test" is received
/// - Just prints message to LCD in this example
/// @param &msg (OSCMessage) incoming OSC message
void routeTest(OSCMessage &msg) {
  int testMsg = msg.getInt(0);

  // Print data to LCD
  M5.Lcd.setCursor(0, 100);
  M5.Lcd.print("/test: ");
  M5.Lcd.print(testMsg);
  M5.Lcd.println("\t");
}

//=============================================================
// SETUP
void setup() {
  // Initialize M5Stick
  M5.begin();

  // Initialize WiFi/UDP
  connectToWiFi();
  udp.begin(inPort);

  // Print network data to LCD
  M5.Lcd.println("Ready\n");
  M5.Lcd.println("Listening to:");
  M5.Lcd.print("IP: ");
  M5.Lcd.println(WiFi.localIP());
  M5.Lcd.print("Port: ");
  M5.Lcd.println(inPort);
}

//=============================================================
// LOOP
void loop() {
  OSCMessage msg;
  int size = udp.parsePacket();

  // If message is received...
  if (size > 0) {
    // 1. Read message
    while (size--) msg.fill(udp.read());

    // 2. Check for errors
    if (msg.hasError()) {
      error = msg.getError();
      Serial.print("error: ");
      Serial.println(error);
    }
    // 3. Execute callback function
    else {
      msg.dispatch("/test", routeTest);
    }
  }

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
