//=============================================================
// File:    M5_RTC_Date.ino
//
// Author:  J. Hathway 2024
//
// Dependencies:
//     - M5StickCPlus library (M5Stack)
//
// Description:
//     - This sketch shows you how to set and read the date 
//       from the M5StickC Plus' built-in RTC.
//=============================================================

#include <M5StickCPlus.h>
  
// Date Settings
RTC_DateTypeDef DateStruct;
int date = 14;
int month = 5;
int year = 1966;
  
void setup() {
  // Initialise M5Stick Pins
  M5.begin();
  
  // Set date
  DateStruct.Date = date;
  DateStruct.Month = month;
  DateStruct.Year = year;
  M5.Rtc.SetDate(&DateStruct);
  
  // LCD display settings
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setRotation(1);
  M5.Lcd.setTextSize(4);
}  
  
void loop() {
  // Get date
  M5.Rtc.GetDate(&DateStruct);
  
  // Print Date
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.printf("%02d-%02d-%04d", DateStruct.Date, DateStruct.Month, DateStruct.Year);
  
  // Short delay (0.5s)
  delay(500);
}