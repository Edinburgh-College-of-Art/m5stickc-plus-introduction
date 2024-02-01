//=======================================================
// File:    AccessPointWithHeaderFile.ino
//
// Author:  J. Hathway 2024
//
// Dependencies:
//     - M5StickCPlus Library (M5Stack).
//     - M5Stick_WiFi.h (J. Hathway).
//
// Description:
//     - Demo of how to use M5StickC-Plus as an 
//       Access Point (AP) with the M5StickC-Plus 
//       header file.
//=======================================================

#include <M5StickCPlus.h>
#include "M5Stick_WiFi.h" // include the header file in your sketch folder

//=======================================================
// **REPLACE THESE VARIABLES WITH YOUR DETAILS**
const char *ssid = "MyNetwork";      // You can choose what your access point is called
const char *password = "MyPassword"; // You can also set a password for your access point
//=======================================================

void setup()
{
    M5.begin();

    // Start Access Point
    startWifiAP(ssid, password);
}

void loop() {}