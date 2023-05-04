//=============================================
// SendOSC example
//
// Button A counts up and sends OSC message
// Button B counts down and sends OSC message
//=============================================

#include <M5StickCPlus.h>

#include "M5Stick_OSC.h"
#include "M5Stick_WiFi.h"

//=============================================
// **CHANGE THESE VARIABLES**
const char *network = "YourNetworkName";
const char *password = "YourPassword";

const char *ip = "10.126.176.199";
const unsigned int port = 8000;

//=============================================
// GLOBAL VARIABLES
int counter = 0;

//=============================================
// SETUP
void setup()
{
  M5.begin();

  // connect to network
  connectToWifi(network, password);

  // IP address and port to send to
  sendTo(ip, port);

  M5.Lcd.setRotation(1);
  M5.Lcd.setTextSize(5);
}

//=============================================
// LOOP
void loop()
{
  //============================================
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

    while (digitalRead(M5_BUTTON_HOME) == LOW) {}
  }

  //============================================
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

    while (digitalRead(M5_BUTTON_RST) == LOW) {}
  }
}