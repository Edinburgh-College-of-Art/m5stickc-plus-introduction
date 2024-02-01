//=============================================================
// File:    OSC_Simple.ino
// 
// Author:  J. Hathway 2024
//
// Dependencies:
//     - M5StickCPlus library (M5Stack)
//     - OSC library (Adrien Freed)
//
// Description:
//     - Send Hello World message via OSC
//=============================================================

#include <M5StickCPlus.h>

#include <BluetoothSerial.h>
#include <OSCMessage.h>
#include <OSCBundle.h>
#include <OSCData.h>

#include <WiFi.h>
#include <WiFiUdp.h>

//=============================================
//*********************************************
// **CHANGE THESE VARIABLES**
const char *network = "YourNetworkName";
const char *password = "YourPassword";

const char *ip = "10.126.176.199";
const unsigned int port = 8000;

String message = "Hello World!"; // Message to send
//*********************************************
//=============================================

// FUNCTION DEFINITIONS
template <typename T>
void sendOscMessage(const char *_route, T _message);
bool connectToWiFi(const char *_ssid, const char *_password);

// GLOBAL VARIABLES
WiFiUDP udp; // upd client

//=============================================
// SETUP
void setup()
{
    // initialise M5Stick
    M5.begin();

    // connect to network
    connectToWifi(network, password);

    // IP address and port to send to
    sendTo(ip, port);
}

//=============================================
// LOOP
void loop()
{
    // send OSC message
    sendOscMessage<String>("/m5stick", message);

    // perform the loop every 15 ms
    // this may be too fast for some routers to enjoy themselves
    // so set it to something less if you need to
    delay(27);
}

//=======================================================

/// Connect to WiFi
/// - Function for connecting to WiFi network
/// @param ssid (const char*) network name
/// @param password (const char*) network password
/// @return status (bool) true = successful, false = failed
bool connectToWiFi(const char *_ssid, const char *_password)
{
  M5.Lcd.print("Connecting");

  // initialise - WIFI_STA = Station Mode
  WiFi.mode(WIFI_STA);
  WiFi.begin(_ssid, _password);

  // start timer
  unsigned long startAttemptTime = millis();

  // while not connected to WiFi AND before timeout
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 30000)
  {
    M5.Lcd.print(".");
    delay(400);
  }

  // Print status to LCD
  if (WiFi.status() != WL_CONNECTED)
  {
    M5.Lcd.println("\nErr: Failed to connect");
    delay(2000);
    return false;
  }
  else
  {
    M5.Lcd.println("\nConnected to:");
    M5.Lcd.println(_ssid);
    delay(2000);
    return true;
  }
}

/// Send OSC Message
/// - template function for sending OSC messages
/// @param route (const char*) message tag
/// @param message message to send 
template <typename T>
void sendOscMessage(const char *_route, T _message)
{
  // init message
  OSCMessage _oscMsg(_route);
  _oscMsg.add((T)_message);

  // send message
  udp.beginPacket(ip, port);
  _oscMsg.send(udp);

  // clear message
  udp.endPacket();
  _oscMsg.empty();
}