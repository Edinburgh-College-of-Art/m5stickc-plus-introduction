//=======================================================
// File:    AccessPoint.h
//
// Author:  J. Hathway 2024
//
// Dependencies:
//     - M5StickCPlus Library (M5Stack).
//     - WiFi Library (Arduino).
//
// Description:
//     - Demo of how to use M5StickC-Plus as
//       an Access Point (AP)
//=======================================================

#include <M5StickCPlus.h>
#include <WiFi.h>

//=======================================================
// **REPLACE THESE VARIABLES WITH YOUR DETAILS**
const char *ssid = "MyNetwork";      // You can choose what your access point is called
const char *password = "MyPassword"; // You can also set a password for your access point
//=======================================================

void setup()
{
    M5.begin();

    M5.Lcd.println("Starting WiFi AP: ");
    M5.Lcd.println(ssid);

    // Initialise as Access Point (WIFI_AP)
    WiFi.mode(WIFI_AP);

    // Start access point - wait for connection
    if (!WiFi.softAP(ssid, password))
    {
        // If failed to start, pause program
        M5.Lcd.println("Err: Access Point Failed");
        while (true);
    }

    // Print IP Address
    M5.Lcd.println("Access Point Created");
    M5.Lcd.println("AP IP Address:");
    M5.Lcd.println(WiFi.softAPIP());
}

void loop() {}