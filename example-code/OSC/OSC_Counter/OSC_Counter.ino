//=============================================================
// File:    OSC_Counter.ino
// 
// Author:  J. Hathway 2024
//
// Dependencies:
//     - M5StickCPlus library (M5Stack)
//     - OSC library (Adrien Freed)
//
// Description:
//     - Send M5STickC-Plus counter data via OSC
//     - Press HOME and RST buttons to change count value
//     - Home = +1, RST = -1
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
//*********************************************
//=============================================

// FUNCTION DEFINITIONS
template <typename T>
void sendOscMessage(const char *_route, T _message);
bool connectToWiFi(const char *_ssid, const char *_password);

// GLOBAL VARIABLES
WiFiUDP udp; // upd client
int counter = 0;

//=============================================
// SETUP
void setup()
{
  M5.begin();

  // connect to network
  connectToWiFi(network, password);

  M5.Lcd.setRotation(1);
  M5.Lcd.setTextSize(5);
}

//=============================================
// LOOP
void loop()
{
  // HOME BUTTON PRESSED
  // Count up
  if (digitalRead(M5_BUTTON_HOME) == LOW)
  {
    // increment counter, print, send osc
    counter++;

    // clear screen
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.setTextSize(5);
    M5.Lcd.print(counter);

    // SEND OSC MESSAGE
    sendOscMessage<int>("/count", counter);

    while (digitalRead(M5_BUTTON_HOME) == LOW)
    {
    }
  }

  // RESET BUTTON PRESSED
  // Count down
  if (digitalRead(M5_BUTTON_RST) == LOW)
  {
    // decrease counter, print, send osc
    counter--;

    // clear screen
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.setTextSize(5);
    M5.Lcd.print(counter);

    // SEND OSC MESSAGE
    sendOscMessage<int>("/count", counter);

    while (digitalRead(M5_BUTTON_RST) == LOW)
    {
    }
  }
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