//=============================================================
// File:    M5_RTC_Time.ino
//
// Author:  J. Hathway 2024
//
// Dependencies:
//     - M5StickCPlus library (M5Stack)
//
// Description:
//     - This sketch shows you how to set and read the time 
//       from the M5StickC Plus' built-in RTC.
//=============================================================

#include <M5StickCPlus.h>
  
// Time Settings
RTC_TimeTypeDef TimeStruct;
int hour = 12;
int minute = 0;
int second = 0;
  
uint8_t lastSecond = 0;
  
void setup() {
  // Initialise M5Stick Pins
  M5.begin();
  
  // Set time
  TimeStruct.Hours = hour;
  TimeStruct.Minutes = minute;
  TimeStruct.Seconds = second;
  M5.Rtc.SetTime(&TimeStruct);
  
  // LCD display settings
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setRotation(1);
  M5.Lcd.setTextSize(5);
}
  
void loop() {
  // Get time
  M5.Rtc.GetTime(&TimeStruct);
  
  // Print if time has changed
  if (lastSecond != TimeStruct.Seconds) {
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.printf("%02d:%02d:%02d", TimeStruct.Hours, TimeStruct.Minutes, TimeStruct.Seconds);
    lastSecond = TimeStruct.Seconds;
  }
}