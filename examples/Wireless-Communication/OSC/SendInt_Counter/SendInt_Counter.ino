//=============================================================
// File:    SendInt_Counter.ino
//
// Author:  J. Hathway 2024
//
// Dependencies:
//     - M5StickCPlus library (M5Stack)
//     - OSC library (Adrian Freed)
//
// Description:
//     - Send M5StickC-Plus counter data via OSC
//     - Press HOME and RST buttons to change count value
//     - Home = +1, RST = -1
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

// Variable to keep track of counter
int counter = 0;

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

/// Send Int OSC Message
/// - function for sending int messages via OSC
/// @param address (const char*) message tag
/// @param message (int) message to send
void sendIntOscMessage(const char *address, int message) {
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

/// Print counter data to LCD
void printCountData() {
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.print(counter);
}

//=============================================
// SETUP
void setup() {
  M5.begin();

  // connect to network
  while (!connectToWiFi()) {}
  udp.begin(localPort);

  M5.Lcd.setRotation(1);
  M5.Lcd.setTextSize(5);
  printCountData();
}

//=============================================
// LOOP
void loop() {
  // HOME BUTTON PRESSED
  // Count up
  if (digitalRead(M5_BUTTON_HOME) == LOW) {
    // increment counter, print, send osc
    counter++;
    printCountData();

    // SEND OSC MESSAGE
    sendIntOscMessage("/count", counter);

    while (digitalRead(M5_BUTTON_HOME) == LOW) {}
  }

  // RESET BUTTON PRESSED
  // Count down
  if (digitalRead(M5_BUTTON_RST) == LOW) {
    // decrease counter, print, send osc
    counter--;
    printCountData();

    // SEND OSC MESSAGE
    sendIntOscMessage("/count", counter);

    while (digitalRead(M5_BUTTON_RST) == LOW) {}
  }
}