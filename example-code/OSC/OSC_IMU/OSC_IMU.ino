//=============================================================
// File:    OSC_IMU.ino
// 
// Author:  J. Hathway 2024
//
// Dependencies:
//     - M5StickCPlus library (M5Stack)
//     - OSC library (Adrien Freed)
//
// Description:
//     - Send M5STickC-Plus IMU data via OSC messages
//=============================================================

#include <M5StickCPlus.h>

#include <BluetoothSerial.h>
#include <OSCMessage.h>
#include <OSCBundle.h>
#include <OSCData.h>

#include <WiFi.h>
#include <WiFiUdp.h>

WiFiClient client;
WiFiUDP upd;

//=============================================
//*********************************************
// **CHANGE THESE VARIABLES**
const char *network = "YourNetworkName"; // <----- your WiFi network's name (as appears on your phone/laptop)
const char *password = "YourPassword"; // <----- your WiFi password

const char *ip = "10.126.176.199"; // <----- IP address of device you are sending to 
const unsigned int port = 115200;  // <----- port on your computer to send to
//*********************************************
//=============================================

// Function declarations
bool connectToWiFi(const char *_ssid, const char *_password);
template <typename T>
void sendOscMessage(const char *_route, T _message);

// Variables for storing the different bits of IMU data
float accX = 0.0F;
float accY = 0.0F;
float accZ = 0.0F;

float gyroX = 0.0F;
float gyroY = 0.0F;
float gyroZ = 0.0F;

float pitch = 0.0F;
float roll  = 0.0F;
float yaw   = 0.0F;

//=============================================================
// SETUP
void setup() {
    M5.begin(); // Init M5StickC Plus

    // Connect to WiFi network
    connectToWiFi(network, password);
    
    delay(1000);
    M5.Lcd.fillScreen(BLACK);
    
    M5.Imu.Init(); // Init IMU

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

    // Get the sensor data from the IMU and store it in our various variables
    static float temp = 0;
    M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
    M5.IMU.getAccelData(&accX, &accY, &accZ);
    M5.IMU.getAhrsData(&pitch, &roll, &yaw);
    M5.IMU.getTempData(&temp);

    // Update the screen on the M5 stick (optional)
    M5.Lcd.setCursor(30, 40);
    M5.Lcd.printf("%6.2f  %6.2f  %6.2f      ", gyroX, gyroY, gyroZ);
    M5.Lcd.setCursor(170, 40);
    M5.Lcd.print("o/s");

    M5.Lcd.setCursor(30, 50);
    M5.Lcd.printf(" %5.2f   %5.2f   %5.2f   ", accX, accY, accZ);
    M5.Lcd.setCursor(170, 50);
    M5.Lcd.print("G");

    M5.Lcd.setCursor(30, 80);
    M5.Lcd.printf(" %5.2f   %5.2f   %5.2f   ", pitch, roll, yaw);

    // Send the data via the wifi network to the computer so that Max can receive the data
    sendOscMessage<float>("/gyroX", gyroX);
    sendOscMessage<float>("/gyroY", gyroY);
    sendOscMessage<float>("/gyroZ", gyroZ);

    sendOscMessage<float>("/accX", accX);
    sendOscMessage<float>("/accY", accY);
    sendOscMessage<float>("/accZ", accZ);

    sendOscMessage<float>("/pitch", pitch);
    sendOscMessage<float>("/roll", roll);
    sendOscMessage<float>("/yaw", yaw);

    // Add a short pause (e.g. 50 milliseconds) between cycles
    // This helps the WiFi router keep up
    delay(50);
}

/// Connect to WiFi
/// - Function for connecting to WiFi network
/// @param ssid (const char*) network name
/// @param password (const char*) network password
/// @return status (bool) true = successful, false = failed
bool connectToWiFi(const char *_ssid, const char *_password)
{
  M5.Lcd.print("Connecting");

  // initialise - WIFI_STA = Station Mode
  WiFi.mode(WIFI_STA);
  WiFi.begin(_ssid, _password);

  // start timer
  unsigned long startAttemptTime = millis();

  // while not connected to WiFi AND before timeout
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 30000)
  {
    M5.Lcd.print(".");
    delay(400);
  }

  // Print status to LCD
  if (WiFi.status() != WL_CONNECTED)
  {
    M5.Lcd.println("\nErr: Failed to connect");
    delay(2000);
    return false;
  }
  else
  {
    M5.Lcd.println("\nConnected to:");
    M5.Lcd.println(_ssid);
    delay(2000);
    return true;
  }
}

/// SendOscMessage<T>
/// - template function for sending OSC messages
/// @param _route (const char*) message route
/// @param _message (T) message
template <typename T>
void sendOscMessage(const char *_route, T _message)
{
    // init message
    OSCMessage _oscMsg(_route);
    _oscMsg.add((T)_message);     

    // send message
    upd.beginPacket(ip, port);
    _oscMsg.send(upd);

    // clear message
    upd.endPacket(); 
    _oscMsg.empty();   
}
