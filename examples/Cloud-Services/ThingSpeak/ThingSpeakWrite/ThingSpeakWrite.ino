//=======================================================
// File:    ThingSpeakWrite.ino
//
// Author:  J. Hathway 2024
//
// Dependencies:
//     - M5StickCPlus Library (M5Stack).
//     - WiFi Library (Arduino).
//     - ThingSpeak Library (MathWorks).
//
// Description:
//     - Write data to the ThingSpeak cloud service.
//     - Write every 15 seconds.
//     - Change counter value by using HOME and RST buttons.
//     - HOME = +1, RST = -1.
//     - Optional "beep" when message sent.
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
const char* writeAPIKey = "ABCDEFGHIJKLM";

bool buzzer = true; // buzz when sent?

const char* statusMessage = "Hello World"; // Status message attached to data
//******************************************
//==========================================

bool connectToWiFi(const char* ssid, const char* pass);

WiFiClient client;
const unsigned long postingInterval = 15000;  // ThingSpeak has a rate limit of 15 seconds
unsigned long lastRequest = 0;

int counter = 0;

//=======================================================
// SETUP
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
  M5.Lcd.setTextSize(4);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.print(counter);
}

//=======================================================
// LOOP
void loop() {
  
  // HOME BUTTON PRESSED
  // - add one to counter
  // - print to LCD
  if (digitalRead(M5_BUTTON_HOME) == LOW) {
    counter += 1;

    // Print count to LCD
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.println(statusMessage);
    M5.Lcd.print(counter);

    // Wait until button released
    while (digitalRead(M5_BUTTON_HOME) == LOW) {}
  }

  
  // RST BUTTON PRESSED
  // - add one to counter
  // - print to LCD
  if (digitalRead(M5_BUTTON_RST) == LOW) {
    counter -= 1;

    // Print count to LCD
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.println(statusMessage);
    M5.Lcd.print(counter);

    // Wait until button released
    while (digitalRead(M5_BUTTON_RST) == LOW) {}
  }

  
  // EVERY 15 SECONDS
  // - Send count data to ThingSpeak channel
  if (millis() - lastRequest > postingInterval) {
    ThingSpeak.setStatus(statusMessage);
    ThingSpeak.setField(1, counter);
    ThingSpeak.writeFields(channelNumber, writeAPIKey);

    // Print to LCD
    M5.Lcd.setCursor(0, 60);
    M5.Lcd.println("Sent");

    // Buzz?
    if (buzzer) {
      M5.Beep.tone(1000);
      delay(250);
      M5.Beep.mute();
    }

    lastRequest = millis();
  }
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