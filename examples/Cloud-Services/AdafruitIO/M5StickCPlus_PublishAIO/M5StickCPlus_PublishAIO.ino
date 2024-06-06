//===================================================================
// File:   M5StickCPlus_PublishAIO.ino
//
// Author: J.Hathway 2024
//
// Description: Press the home/rst buttons on the M5Stick to increase/
//              decrease the counter and publish the data to AdafruitIO
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
const char* aioFeed = "MyFeed";

bool buzzer = false; // buzz when sent?
//******************************************
//==========================================

AdafruitIO_WiFi io(aioUsername, aioKey, network, password);
AdafruitIO_Feed *feed = io.feed(aioFeed);

int counter = 0;

unsigned long postingInterval = 3000;
unsigned long lastRequest = millis();

//=======================================================
// SETUP
void setup() {
  M5.begin();
  M5.Lcd.print("Connecting to AIO");

  // Connect to io.adafruit.com
  io.connect();

  // Wait for a connection
  while (io.status() < AIO_CONNECTED) {
    M5.Lcd.print(".");
    delay(500);
  }

  M5.Lcd.println();
  M5.Lcd.println(io.statusText());
  delay(1000);

  // Font settings
  M5.Lcd.setTextSize(4);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.print(counter);
}

//=======================================================
// LOOP
void loop() {
  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();

  // HOME BUTTON PRESSED
  // - add one to counter
  // - print to LCD
  if (digitalRead(M5_BUTTON_HOME) == LOW) {
    counter += 1;

    // Print count to LCD
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0, 0);
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
    M5.Lcd.print(counter);

    // Wait until button released
    while (digitalRead(M5_BUTTON_RST) == LOW) {}
  }


  // EVERY 3 SECONDS
  // - Send count AIO Feed
  if (millis() - lastRequest > postingInterval) {
    feed->save(counter);

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