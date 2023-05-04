//=======================================================
// File:    ThingSpeakRead.ino
//
// Author:  J. Hathway 2024
//
// Dependencies:
//     - M5StickCPlus Library (M5Stack).
//     - WiFi Library (Arduino).
//     - ThingSpeak Library (MathWorks).
//
// Description:
//     - Read data from the ThingSpeak cloud service.
//     - Read every 15 seconds and print to LCD.
//     - Optional "beep" when message received.
//=======================================================

#include <M5StickCPlus.h>
#include <ThingSpeak.h>
#include <WiFi.h>

//==========================================
//******************************************
// ***CHANGE THESE VARIABLES***
// WiFi details
const char* network = "UoE-Device";
const char* password = "12345678";

// ThingSpeak channel details
unsigned long channelNumber = 1234567;
const char* readAPIKey = "ABCDEFGHIJKLM";

bool buzzer = true;  // buzz when sent?
//******************************************
//==========================================

bool connectToWiFi(const char* ssid, const char* pass);

WiFiClient client;
const unsigned long postingInterval = 15000;  // ThingSpeak has a rate limit of 15 seconds
unsigned long lastRequest = 0;

void setup() {
  M5.begin();

  // Connect to WiFi
  while (!connectToWiFi(network, password)) {
    delay(1000);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.fillScreen(BLACK);
  }

  delay(1000);

  // Start ThingSpeak client
  ThingSpeak.begin(client);

  // Font settings
  M5.Lcd.setRotation(1);
  M5.Lcd.setTextSize(3);
}

//=======================================================
// LOOP
void loop() {

  // EVERY 15 SECONDS
  // - read from ThingSpeak channel
  // - print value to LCD
  if (millis() - lastRequest > postingInterval) {
    lastRequest = millis();

    int statusCode = ThingSpeak.readMultipleFields(channelNumber, readAPIKey);

    if (statusCode == 200) {
      // Read value from ThingSpeak channel
      String statusMessage = ThingSpeak.getStatus();  // Status message
      int incomingValue = ThingSpeak.readIntField(channelNumber, 1, readAPIKey);

      // Buzz?
      if (buzzer) {
        M5.Beep.tone(1000);
        delay(250);
        M5.Beep.mute();
      }

      // Print to LCD
      M5.Lcd.fillScreen(BLACK);
      M5.Lcd.setCursor(0, 0);
      M5.Lcd.println(statusMessage);
      M5.Lcd.println(incomingValue);
    } else {
      M5.Lcd.fillScreen(BLACK);
      M5.Lcd.setCursor(0, 0);
      M5.Lcd.println("Err. msg not received");
    }
  }

  delay(25);
}

//=======================================================
// CONNECT TO WIFI FUNCTION
bool connectToWiFi(const char* ssid, const char* pass) {
  M5.Lcd.print("Connecting");

  // initialise - WIFI_STA = Station Mode
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  // start timer
  unsigned long startAttemptTime = millis();

  // while not connected to WiFi AND before timeout
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 30000) {
    M5.Lcd.print(".");
    delay(400);
  }

  // Print status to LCD
  if (WiFi.status() != WL_CONNECTED) {
    M5.Lcd.println("\nErr: Failed to connect");
    delay(2000);
    return false;
  } else {
    M5.Lcd.println("\nConnected to:");
    M5.Lcd.println(ssid);
    delay(2000);
    return true;
  }
}