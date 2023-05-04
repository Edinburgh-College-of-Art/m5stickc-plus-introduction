//===================================================================
// File:   M5StickCPlus_SubscribeAIO.ino
//
// Author: J Hathway 2023
//
// Description: Sketch receives data from AdafruitIO and prints
//              it to LCD screen.
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

  // init callback function on message received
  myFeed->onMessage(handleMessage);
  myFeed->get();

  // print status to LCD
  M5.Lcd.println();
  M5.Lcd.println(io.statusText());

}

//===================================================================
// LOOP
void loop() {
  // keep client connected to AIO
  io.run();
}

//===================================================================
// CALLBACK FUNCTION
// function called when message is received
void handleMessage(AdafruitIO_Data *data) {
  // print data to LCD
  M5.Lcd.print("received <- ");
  M5.Lcd.println(data->value());
}
