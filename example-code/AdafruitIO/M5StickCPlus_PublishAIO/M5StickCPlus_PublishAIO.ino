//===================================================================
// File:   M5StickCPlus_PublishAIO.ino
//
// Author: J Hathway 2023
//
// Description: Press the home button on the M5STick to increment
//              the counter and publish the data to AdafruitIO
//
// Dependencies:- M5StickCPlus 0.0.8 (M5Stack) 
//              - Adafruit IO Arduino 4.2.3 (Adafruit)
//===================================================================           

#include <M5StickCPlus.h>
#include <AdafruitIO_WiFi.h>

//===================================================================
// CHANGE THESE VARIABLES

// Adafruit IO
#define AIO_USERNAME "user"
#define AIO_KEY "key"
#define AIO_FEED "feed"

// WiFi
#define NETWORK_NAME "ssid"
#define NETWORK_PASSWORD "password"

//===================================================================
// Adafruit IO Objects
AdafruitIO_WiFi io(AIO_USERNAME, AIO_KEY, NETWORK_NAME, NETWORK_PASSWORD);
AdafruitIO_Feed *myFeed = io.feed(AIO_FEED);

// stores counter value
int counter = 0;

//===================================================================
// SETUP
void setup() {
  // init M5Stick
  M5.begin();

  // connect to AIO
  M5.Lcd.print("Connecting to Adafruit IO");
  io.connect();

  // wait for connection
  while (io.status() < AIO_CONNECTED) {
    M5.Lcd.print(".");
    delay(300);
  }

  // print status to LCD
  M5.Lcd.println();
  M5.Lcd.println(io.statusText());
}

//===================================================================
// LOOP
void loop() {
  // keep client connected to AIO
  io.run();

  // if button pressed...
  if (digitalRead(M5_BUTTON_HOME) == LOW) {
    // increment counter
    counter++;

    //print count
    M5.Lcd.print("sending -> ");
    M5.Lcd.println(counter);

    // send counter to AIO
    myFeed->save(counter);

    // add delay to slow frequency of messages sent to AIO
    delay(3000);

    // wait for button to be released
    while (digitalRead(M5_BUTTON_HOME) == LOW);
  }
}
