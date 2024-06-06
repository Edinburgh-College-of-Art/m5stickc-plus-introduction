//=============================================================
// File:    M5_IMU_Accelerometer.ino
//
// Author:  J. Hathway 2024
//
// Dependencies:
//     - M5StickCPlus library (M5Stack)
//
// Description:
//     - This sketch gathers accelerometer data from the 
//       M5StickC Plus' built-in IMU. 
//
//     - This data is then printed to the onboard LCD display.
//=============================================================

#include <M5StickCPlus.h>
    
// Variables for storing 3-axis accelerometer data
float accX, accY, accZ;
    
void setup() {
  // Initialise M5Stick Pins
  M5.begin();
   
  // LCD settings
  M5.Lcd.setRotation(1);
  M5.Lcd.setTextSize(3);
   
  // Start IMU chip
  // return 0 if OK
  // return -1 if unsuccessful
  int status = M5.IMU.Init();
    
  // If IMU chip not recognised, do not continue
  if (status != 0) {
    M5.Lcd.print("IMU not\n recognised");
    while (true){}
  }
}
   
void loop() {
  // Get accelerometer data
  M5.IMU.getAccelData(&accX, &accY, &accZ);
  
  // Print data
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.print("AccX:");
  M5.Lcd.println(accX);
  M5.Lcd.print("AccY:");
  M5.Lcd.println(accY);
  M5.Lcd.print("AccZ:");
  M5.Lcd.println(accZ);
  
  // Short delay (100ms)
  delay(100);
}