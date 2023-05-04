//==============================================
// File:    M5StickCPlus_SendESPNOW
//
// Author:  J. Hathway
//
// Description:
//     - Send incoming ESP NOW messages
//     - Repeat every 10 seconds
//===============================================

#include <M5StickCPlus.h>
#include "M5Stick_ESPNOW.h"

// Message to send
// ***MUST be same data type as receiver
String outgoingMessage = "AhoyHoy";

void setup()
{
  // initialise M5Stick
  M5.begin();

  // initialise ESPNOW send
  espInitSend();

  // MAC addresses to send to
  uint8_t macAddress[] = {0x4C, 0x75, 0x25, 0x9F, 0x64, 0xF0};
  uint8_t macAddress2[] = {0x4C, 0x75, 0x25, 0x9F, 0x09, 0x28};
  
  // pair with MAC addresses
  sendTo(macAddress);
  sendTo(macAddress2);
}

void loop()
{
  // send message every 10 seconds
  // ***MUST specify data type 
  M5.Lcd.println("Sending message:\n" + outgoingMessage);
  espSend<String>(outgoingMessage);
  delay(10000);

  // clear screen
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.fillScreen(BLACK);
}
