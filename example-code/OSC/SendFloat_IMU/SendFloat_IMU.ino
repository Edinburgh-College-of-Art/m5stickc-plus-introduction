//=============================================================
// File:    SendFloat_IMU.ino
//
// Author:  J. Hathway 2024
//
// Dependencies:
//     - M5StickCPlus library (M5Stack)
//     - OSC library (Adrian Freed)
//
// Description:
//     - Send M5StickC-Plus IMU data via OSC messages
//=============================================================

#include <M5StickCPlus.h>

#include <WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>

//=============================================
//*********************************************
// **CHANGE THESE VARIABLES**
const char *ssid = "NetworkName";          // <----- your WiFi network's name (as appears on your phone/laptop)
const char *password = "NetworkPassword";  // <----- your WiFi password

const IPAddress outIp(192, 168, 23, 123);  // <----- IP address of receiving device
const unsigned int outPort = 8000;          // <----- Network port you are sending to
                                            //        **Must match inPort on receiving device
//*********************************************
//=============================================

// Object for OSC/UDP
WiFiUDP udp;

// Network port for incoming messages
const unsigned int localPort = 8000;  // This is not strictly needed for sending messages

// Variables for storing the different bits of IMU data
float accX = 0.f;
float accY = 0.f;
float accZ = 0.f;

float gyroX = 0.f;
float gyroY = 0.f;
float gyroZ = 0.f;

float pitch = 0.f;
float roll = 0.f;
float yaw = 0.f;

//=============================================================
// FUNCTIONS

/// Connect to WiFi
/// - Function for connecting to WiFi network
/// @return status (bool) true = successful, false = failed
bool connectToWiFi() {
  M5.Lcd.print("Connecting");

  // initialise - WIFI_STA = Station Mode
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

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
    M5.Lcd.println(WiFi.localIP());

    delay(2000);
    return true;
  }
}

/// Send float OSC Message
/// - function for sending float messages via OSC
/// @param address (const char*) message tag
/// @param message (float) message to send
void sendFloatOscMessage(const char *address, float message) {
  // init message
  OSCMessage oscMsg(address);
  oscMsg.add(message);

  // send message
  udp.beginPacket(outIp, outPort);
  oscMsg.send(udp);

  // clear message
  udp.endPacket();
  oscMsg.empty();
}

//=============================================================
// SETUP
void setup() {
  M5.begin();  // Init M5StickC Plus

  // Connect to WiFi network
  while (!connectToWiFi()) {}
  udp.begin(localPort);

  delay(1000);
  M5.Lcd.fillScreen(BLACK);

  M5.Imu.Init();  // Init IMU

  // Font settings
  M5.Lcd.setRotation(3);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(1);

  M5.Lcd.setCursor(80, 15);  // set the cursor location
  M5.Lcd.println("IMU TEST");

  M5.Lcd.setCursor(30, 30);
  M5.Lcd.println("  X       Y       Z");

  M5.Lcd.setCursor(30, 70);
  M5.Lcd.println("  Pitch   Roll    Yaw");
}

//=============================================================
// LOOP
void loop() {

  // 1. GET IMU DATA
  static float temp = 0;
  M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);  // Gyroscopic data
  M5.IMU.getAccelData(&accX, &accY, &accZ);    // Accelerometer data
  M5.IMU.getAhrsData(&pitch, &roll, &yaw);     // AHRS data

  // 2. PRINT DATA TO M5 LCD (optional)
  // Gyroscopic data
  M5.Lcd.setCursor(30, 40);
  M5.Lcd.printf("%6.2f  %6.2f  %6.2f      ", gyroX, gyroY, gyroZ);
  M5.Lcd.setCursor(170, 40);
  M5.Lcd.print("o/s");

  // Accelerometer data
  M5.Lcd.setCursor(30, 50);
  M5.Lcd.printf(" %5.2f   %5.2f   %5.2f   ", accX, accY, accZ);
  M5.Lcd.setCursor(170, 50);
  M5.Lcd.print("G");

  // AHRS data
  M5.Lcd.setCursor(30, 80);
  M5.Lcd.printf(" %5.2f   %5.2f   %5.2f   ", pitch, roll, yaw);

  // 3. SEND DATA VIA OSC
  // Gyroscopic data
  sendFloatOscMessage("/gyroX", gyroX);
  sendFloatOscMessage("/gyroY", gyroY);
  sendFloatOscMessage("/gyroZ", gyroZ);

  // Accelerometer data
  sendFloatOscMessage("/accX", accX);
  sendFloatOscMessage("/accY", accY);
  sendFloatOscMessage("/accZ", accZ);

  // AHRS data
  sendFloatOscMessage("/pitch", pitch);
  sendFloatOscMessage("/roll", roll);
  sendFloatOscMessage("/yaw", yaw);

  // Add a short pause (e.g. 50 milliseconds) between cycles
  // This helps the WiFi router keep up
  delay(50);
}