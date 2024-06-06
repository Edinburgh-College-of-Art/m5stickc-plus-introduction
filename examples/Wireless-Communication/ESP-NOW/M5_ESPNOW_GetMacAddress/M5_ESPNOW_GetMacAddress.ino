//==============================================================
// File:    M5_ESPNOW_GetMacAddress.ino
//
// Author:  J. Hathway 2024
//
// Dependencies:
//     - M5StickCPlus library (M5Stack)
//
// Description:
//     - This sketch will print the device MAC address to both
//       serial monitor and LCD display.
//==============================================================

#include <M5StickCPlus.h>
#include <WiFi.h>

void setup()
{
  M5.begin();
  Serial.begin(115200);

  M5.Lcd.setTextSize(2);
  M5.Lcd.setRotation(1);

  M5.Lcd.println("MAC Address:");
  M5.Lcd.println(WiFi.macAddress());

  Serial.println("MAC Address:");
  Serial.println(WiFi.macAddress());
}

void loop() {}