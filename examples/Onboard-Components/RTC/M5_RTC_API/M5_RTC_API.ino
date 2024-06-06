//=============================================================
// File:    M5_RTC_API.ino
//
// Author:  J. Hathway 2024
//
// Dependencies:
//     - M5StickCPlus library (M5Stack)
//     - Arduino JSON library (Benoît Blanchon)
//
// Description:
//     - This sketch uses the WorldTime.org API to gather 
//       current time and date information.
//
//     - This information is then used to set the time and date
//       on the M5StickC Plus' RTC module.
//
//     - This time and date information is then printed to the 
//       onboardLCD display.
//
//     - You will need to replace the ssid and password
//       variables with your own Wi-Fi network name and
//       password.
//=============================================================

#include <M5StickCPlus.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
    
//=======================================================
// **REPLACE THESE VARIABLES WITH YOUR DETAILS**
const char* ssid = "YourWifiName";
const char* password = "YourWifiPassword";
//=======================================================
   
// API Request URL
const char* requestURL = "https://worldtimeapi.org/api/timezone/Europe/London";
    
// Time and Date structures
RTC_TimeTypeDef TimeStruct;
RTC_DateTypeDef DateStruct;
uint8_t lastSecond = 0;
  
// Function definitions
bool connectToWiFi(const char* ssid, const char* password);
String deserialise();
String makeAPIRequest();
  
//=======================================================
// SETUP
void setup() {
  // Start M5
  M5.begin();
  
  // Connect to WiFi
  // Do not continue if not connected
  while (!connectToWiFi(ssid, password)) {}
  
  // Get date and time
  String datetime = "";
  
  while (datetime == "") {
    M5.Lcd.println("Getting data...");
    datetime = getDateTime(); // Store date-time string here
  }
  
  // Set Date
  DateStruct.Date = datetime.substring(5, 7).toInt();
  DateStruct.Month = datetime.substring(8, 10).toInt();
  DateStruct.Year = datetime.substring(0, 4).toInt();
  M5.Rtc.SetDate(&DateStruct);
  
  // Set Time
  TimeStruct.Hours = datetime.substring(11, 13).toInt();
  TimeStruct.Minutes = datetime.substring(14, 16).toInt();
  TimeStruct.Seconds = datetime.substring(17, 19).toInt();
  M5.Rtc.SetTime(&TimeStruct);
  
  // LCD display settings
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setRotation(1);
  M5.Lcd.setTextSize(3);
}
  
//=======================================================
// LOOP
void loop() {
  // Get Time and Date
  M5.Rtc.GetDate(&DateStruct);
  M5.Rtc.GetTime(&TimeStruct);
  
  // Print if time has changed
  if (lastSecond != TimeStruct.Seconds) {
    M5.Lcd.setCursor(0, 0);
  
    // Time
    M5.Lcd.setTextSize(5);
    M5.Lcd.printf("%02d:%02d:%02d\n", TimeStruct.Hours, TimeStruct.Minutes, TimeStruct.Seconds);
  
    // Date (dd-mm-yyyy)
    M5.Lcd.setTextSize(4);
    M5.Lcd.printf("%02d-%02d-%04d", DateStruct.Date, DateStruct.Month, DateStruct.Year);
  
    lastSecond = TimeStruct.Seconds;
  }
}
  
//============================================================
// MAKE API REQUEST
String makeAPIRequest() {
  // Make API Request
  HTTPClient client;
  client.begin(requestURL);
  
  // Get status
  int status = client.GET();
  
  if (status == 0) {
    M5.Lcd.println("Connection failed");
    return "";
  }
  
  // Retrieve JSON response
  String payload = client.getString();
  
  // End HTTP connection
  client.end();
  
  // Return payload
  return payload;
}
  
//=======================================================
// DESERIALIZE JSON - retrieve date/time data
String getDateTime() {
  // Get JSON response
  String payload = makeAPIRequest();
  if (payload == "") return "";
  
  // Deserialize JSON
  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, payload);
  
  if (error) {
    M5.Lcd.print("deserializeJson() failed: ");
    M5.Lcd.println(error.c_str());
    return "";
  }
  
  // Retrieve datetime string
  const char* datetime = doc["datetime"];
  return datetime;
}
  
//============================================================
// Connect to WiFi Function
bool connectToWiFi(const char* ssid, const char* password) {
  M5.Lcd.printf("Connecting to\n%s", ssid);
  
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
    M5.Lcd.println("\nConnected");
    delay(2000);
    return true;
  }
}