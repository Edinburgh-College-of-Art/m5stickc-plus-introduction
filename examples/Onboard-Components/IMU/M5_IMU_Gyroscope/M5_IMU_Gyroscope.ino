//=============================================================
// File:    M5_IMU_Gyroscope.ino
//
// Author:  J. Hathway 2024
//
// Dependencies:
//     - M5StickCPlus library (M5Stack)
//
// Description:
//     - This sketch gathers gyroscopic data from the 
//       M5StickC Plus' built-in IMU. 
//
//     - This data is then printed to the onboard LCD display.
//=============================================================

#include <M5StickCPlus.h>
    
// Variables for storing 3-axis gyroscope data
float gyroX, gyroY, gyroZ;
    
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
  // Get gyroscope data
  M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
  
  // Print data
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.print("GyroX:");
  M5.Lcd.println(gyroX);
  M5.Lcd.print("GyroY:");
  M5.Lcd.println(gyroY);
  M5.Lcd.print("GyroZ:");
  M5.Lcd.println(gyroZ);
  
  // Short delay (500ms)
  delay(500);
}