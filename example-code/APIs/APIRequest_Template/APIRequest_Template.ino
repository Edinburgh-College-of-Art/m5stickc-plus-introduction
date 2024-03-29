//=============================================================
// File:    APIRequest_Template
//
// Author:  J.Hathway 2024
//
// Description:
//     - Template sketch for making an API request from an 
//       M5StickC-Plus.
//     - Example request gathers data on current temperature in
//       Edinburgh (https://open-meteo.com/).
//
// Dependencies:
//     - M5StickCPlus Library 0.1.0 (M5Stack)
//     - ArduinoHTTPClient Library 0.5.0 (Arduino)
//     - ArduinoJson Library 7.0.3 (Benoit Blanchon)
//=============================================================

#include <ArduinoJson.h>
#include <M5StickCPlus.h>
#include <HTTPClient.h>
#include <WiFi.h>

//******************************************
// ***CHANGE THESE VARIABLES***
// WiFi details
const char* network = "UoE-Device";  // network you are connecting to
const char* password = "uThnYvRm";   // network password

// Replace this with your request URL
// This example gets the current temperature in Edinburgh
String requestURL = "https://api.open-meteo.com/v1/forecast?latitude=55.9521&longitude=-3.1965&current=temperature_2m";

/*
  *OPTIONAL* You may need to increase the size of this object
  if you are expecting a particularly large HTTP response.

  Consult https://arduinojson.org/v7/assistant for more info
*/
StaticJsonDocument<1500> doc;
//==========================================

void getData();
bool connectToWiFi(const char* ssid, const char* pass);

//============================================
// SETUP
void setup() {
  Serial.begin(115200);

  // M5StickC Plus Init
  M5.begin();

  // Connect to WiFi
  connectToWiFi(network, password);
  delay(1000);

  //================================================
  // MAKE GET REQUEST
  getData();

  //================================================
  // ***DESERIALIZE JSON DATA***

  /* 
    Once you have received a response from the API, you will need to 
    deserialize the data to use it in your sketch.

    You will need to consult https://arduinojson.org/v7/assistant for the 
    correct code for deserializing your particularAPI response JSON.
  
    Replace all of this code with the code generated by the JSON assistant
  */

  float latitude = doc["latitude"];                                  // latitude
  float longitude = doc["longitude"];                                // longitude
  double generationtime_ms = doc["generationtime_ms"];               // generation time
  int utc_offset_seconds = doc["utc_offset_seconds"];                // offset (seconds)
  const char* timezone = doc["timezone"];                            // timezone
  const char* timezone_abbreviation = doc["timezone_abbreviation"];  // timezone abbreviation
  int elevation = doc["elevation"];                                  // elevation (m)

  JsonObject current_units = doc["current_units"];
  const char* current_units_time = current_units["time"];                      // Time units
  const char* current_units_interval = current_units["interval"];              // Time units interval
  const char* current_units_temperature_2m = current_units["temperature_2m"];  // Temperature units

  JsonObject current = doc["current"];
  const char* current_time = current["time"];                // Current time
  int current_interval = current["interval"];                // Current interval
  float current_temperature_2m = current["temperature_2m"];  // Current temperature

  //==============================================
  // PRINT DATA
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.setTextSize(2);

  // Coordinates
  M5.Lcd.println("Location:");
  M5.Lcd.print(latitude);
  M5.Lcd.println(",");
  M5.Lcd.println(longitude);
  M5.Lcd.println();

  // Time
  M5.Lcd.println(current_time);
  M5.Lcd.println();

  // Temperature
  M5.Lcd.println("Temp:");
  M5.Lcd.print(current_temperature_2m);
  M5.Lcd.println(current_units_temperature_2m);
}

//============================================
// LOOP
void loop() {
}

//=======================================================
// MAKE API GET REQUEST FUNCTION
// This function makes the API request using the url defined
// at the top of the sketch (requestURL)
void getData() {
  // set up HTTP Client
  HTTPClient client;

  // access URL
  client.begin(requestURL.c_str());

  // send GET Request
  int httpCode = client.GET();

  // if request is successful...
  if (httpCode > 0) {
    // store recieved data
    String payload = client.getString();
    Serial.println("Statuscode: " + String(httpCode));

    // check for error
    DeserializationError error = deserializeJson(doc, payload);

    if (error) {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.c_str());
      return;
    } else {
      Serial.println("deserializeJson() successful");

      delay(1000);
      M5.Lcd.fillScreen(BLACK);
      M5.Lcd.setCursor(0, 0);
    }

    // end HTTP call
    client.end();
  } else {
    // if request is NOT successful, print error message
    Serial.println("Error on HTTP request.");
  }
}

//=======================================================
// CONNECT TO WIFI FUNCTION
// This function starts the WiFi connection
bool connectToWiFi(const char* ssid, const char* pass) {
  M5.Lcd.print("Connecting");

  // initialise - WIFI_STA = Station Mode
  WiFi.mode(WIFI_STA);
  WiFi.begin(network, password);

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