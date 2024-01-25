//=======================================================
// File:    ConnectToWiFi.h
//
// Author:  J. Hathway 2024
//
// Dependencies:
//     - M5StickCPlus Library (M5Stack).
//     - WiFi Library (Arduino).
//
// Description:
//     - Demo of how to connect M5StickC-Plus to WiFi.
//=======================================================

#include <M5StickCPlus.h>
#include <WiFi.h>

//=======================================================
// **REPLACE THESE VARIABLES WITH YOUR DETAILS**
const char *ssid = "MyNetwork";
const char *password = "MyPassword";
//=======================================================

void setup()
{
    M5.begin();

    M5.Lcd.print("Connecting");

    // initialise in station mode (WIFI_STA)
    WiFi.mode(WIFI_STA);

    // Start connection
    WiFi.begin(ssid, password);

    // Wait until connected
    while (WiFi.status() != WL_CONNECTED)
    {
        M5.Lcd.print(".");
        delay(400);
    }

    M5.Lcd.println("\nConnected to:");
    M5.Lcd.println(ssid);
}

void loop() {}