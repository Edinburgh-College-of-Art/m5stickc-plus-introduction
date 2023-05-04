//==============================================
// OSC_IMU example
//
// Send M5StickC-Plus IMU data via OSC messages
//==============================================

#include <M5StickCPlus.h>

#include "M5Stick_OSC.h"
#include "M5Stick_WiFi.h"

//=============================================
// **CHANGE THESE VARIABLES**
const char *network = "YourNetworkName";
const char *password = "YourPassword";

const char *ip = "10.126.204.251";
const unsigned int port = 8000;

//=============================================
// GLOBAL VARIABLES
float pitch = 0.f;
float roll = 0.f;
float yaw = 0.f;

//=============================================
// SETUP
void setup()
{
  // initialise M5Stick
  M5.begin();

  // connect to network
  connectToWifi(network, password);

  // IP address and port to send to
  sendTo(ip, port);

  // initialise IMU
  M5.Imu.Init();
  M5.Axp.EnableCoulombcounter();

  // prepare LCD screen
  M5.Lcd.setRotation(3);    // rotate
  M5.Lcd.fillScreen(BLACK); // clear

  // print network and host IP
  M5.Lcd.setCursor(15, 105);
  M5.Lcd.printf("network: %s", network);
  M5.Lcd.setCursor(15, 115);
  M5.Lcd.printf("IP: %s", ip);

  M5.Lcd.setTextSize(3);    // text size
}

//=============================================
// LOOP
void loop()
{
  // get IMU data
  M5.IMU.getAhrsData(&pitch, &roll, &yaw);

  // print data to LCD screen
  M5.Lcd.setCursor(15, 10);
  M5.Lcd.printf("PITCH: %5.1f", pitch);
  M5.Lcd.setCursor(15, 35);
  M5.Lcd.printf("ROLL: %5.1f", roll);
  M5.Lcd.setCursor(15, 60);
  M5.Lcd.printf("YAW: %5.1f", yaw);

  // only send OSC messages when connected
  if (WL_CONNECTED) {
    sendOscMessage<float>("/pitch", pitch);
    sendOscMessage<float>("/roll", roll);
    sendOscMessage<float>("/yaw", yaw);
  }

  // perform the loop every 15 ms
  // this may be too fast for some routers to enjoy themselves
  // so set it to something less if you need to
  delay(27);
}