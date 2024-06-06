//=============================================================
// File:    M5_API_ExampleRequest.ino
//
// Author:  J. Hathway 2024
//
// Dependencies:
//     - M5StickCPlus library (M5Stack)
//     - Arduino JSON library (Benoît Blanchon)
//
// Description:
//     - This sketch makes an example API request from an 
//       M5StickC Plus using the https://open-meteo.com/ API.
//
//     - This sketch will then deserialize the response to
//       retrieve temperature, rainfall, and air pressure data 
//       and print it to the onboard LCD display.
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
const char* ssid = "NetworkName";
const char* password = "NetworkPassword";
//=======================================================
  
// API Request URL
const char* requestURL = "https://api.open-meteo.com/v1/forecast?latitude=55.9521&longitude=-3.1965&current=temperature_2m,rain,pressure_msl";
  
// Function definitions
bool connectToWiFi(const char* ssid, const char* password);
  
//=======================================================
// SETUP
void setup() {
  // Start M5Stick
  M5.begin();
  
  // Connect to WiFi
  // Do not continue if not connected
  while (!connectToWiFi(ssid, password)) {}
  
  // Make API request
  // Get JSON response
  String payload;
  makeAPIRequest(payload);
  
  // Deserialize JSON
  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, payload);
  
  if (error) {
    M5.Lcd.print("deserializeJson() failed: ");
    M5.Lcd.println(error.c_str());
    while (true) {}
  }
  
  // Retrieve data
  JsonObject current = doc["current"];
  
  float current_temperature_2m = current["temperature_2m"];  // temperature
  float current_rain = current["rain"];                      // rain
  float current_pressure_msl = current["pressure_msl"];      // pressure
  
  // Screen setttings
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
  
  // Print data to LCD
  M5.Lcd.setTextSize(2);
  M5.Lcd.printf("Temp:%.1fC\n", current_temperature_2m);
  M5.Lcd.printf("Rain:%.1fmm\n", current_rain);
  M5.Lcd.printf("Pres:%.0f", current_pressure_msl);
}
  
//=======================================================
// LOOP
void loop() {}
  
//============================================================
// API Request Function
void makeAPIRequest(String& payload) {
  // Start HTTP client
  HTTPClient client;
  client.begin(requestURL);
  
  // Get status
  int status = client.GET();
  
  if (status == 0) {
    M5.Lcd.println("Connection failed");
    while (true) {}
  }
  
  // Retrieve JSON response
  payload = client.getString();
  client.end();  // End HTTP connection
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