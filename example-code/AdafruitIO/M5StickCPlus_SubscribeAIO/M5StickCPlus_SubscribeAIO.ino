//===================================================================
// File:   M5StickCPlus_PublishAIO.ino
//
// Author: J.Hathway 2024
//
// Description: Sketch receives data from AdafruitIO and prints
//              it to LCD screen.
//
// Dependencies:- M5StickCPlus Library 0.1.0 (M5Stack)
//              - Adafruit IO Arduino Library 4.2.9 (Adafruit)
//===================================================================

#include <AdafruitIO_WiFi.h>
#include <M5StickCPlus.h>

//==========================================
//******************************************
// ***CHANGE THESE VARIABLES***
// WiFi details
const char* network = "UoE-Device";
const char* password = "12345678";

// Adafriut IO details
const char* aioUsername = "Username";
const char* aioKey = "aio_xxxxxxxxxxxxxxxxxxxxxxxxxxxx";
const char* aioFeed = "Counter";

bool buzzer = false;  // buzz when received?
//******************************************
//==========================================

void handleMessage(AdafruitIO_Data* data);

AdafruitIO_WiFi io(aioUsername, aioKey, network, password);
AdafruitIO_Feed* feed = io.feed(aioFeed);

unsigned long postingInterval = 3000;
unsigned long lastRequest = millis();

//=======================================================
// SETUP
void setup() {
  M5.begin();
  M5.Lcd.print("Connecting to AIO");

  // Connect to io.adafruit.com
  io.connect();

  // Wait for connection
  while (io.status() < AIO_CONNECTED) {
    M5.Lcd.print(".");
    delay(300);
  }

  // Set up message handler for feed
  feed->onMessage(handleMessage);
  feed->get();

  M5.Lcd.println();
  M5.Lcd.println(io.statusText());
  delay(1000);

  // Font settings
  M5.Lcd.setTextSize(4);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.setRotation(1);
  M5.Lcd.print("Ready...");
}

//=======================================================
// LOOP
void loop() {
  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();
}

//=======================================================
// MESSAGE HANDLER
// This function is executed when a message is received
void handleMessage(AdafruitIO_Data* data) {
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.println("received:");
  M5.Lcd.println(data->value());

  // Buzz?
  if (buzzer) {
    M5.Beep.tone(1000);
    delay(250);
    M5.Beep.mute();
  }
}