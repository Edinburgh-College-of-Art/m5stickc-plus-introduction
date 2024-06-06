//=============================================================
// File:    M5_IMU_AHRS.ino
//
// Author:  J. Hathway 2024
//
// Dependencies:
//     - M5StickCPlus library (M5Stack)
//
// Description:
//     - This sketch gathers AHRS data from the M5StickC Plus' 
//       built-in IMU. 
//       
//     - This data is then printed to the onboard LCD display.
//=============================================================

#include <M5StickCPlus.h>
    
// Variables for storing AHRS data
float pitch, roll, yaw;
    
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
  // Get AHRS data
  M5.IMU.getAhrsData(&pitch, &roll, &yaw);
  
  // Print data
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.print("Pitch:");
  M5.Lcd.println(pitch);
  M5.Lcd.print("Roll: ");
  M5.Lcd.println(roll);
  M5.Lcd.print("Yaw:  ");
  M5.Lcd.println(yaw);
  
  // Short delay (100ms)
  delay(100);
}