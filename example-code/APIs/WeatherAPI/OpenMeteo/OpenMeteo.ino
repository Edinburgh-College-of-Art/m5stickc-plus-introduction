//=============================================================
// File:    OpenMeteo.ino
//
// Author:  J.Hathway 2024
//
// Description:
//     - Gather weather data using Open-Meteo API 
//       https://open-meteo.com/
//     - Print data to M5StickC Plus LCD
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
const char* network = "UoE-Device";
const char* password = "uThnYvRm";

String longitude = "3.44";
String latitude = "55.38";

// How far in the future do we want the forecast?
// 0 = today
int daysInAdvance = 0; 
//==========================================

void getData();
bool connectToWiFi(const char* ssid, const char* pass);

String hostURL = "https://api.open-meteo.com/v1/forecast?";                                // Open Meteo url
String coordinates = "latitude=" + latitude + "&longitude=" + longitude;                   // What location are we looking for?
String headers = "&daily=temperature_2m_max,temperature_2m_min&timezone=Europe%2FLondon";  // What data are we asking for?

// Final request URL
String url = hostURL + coordinates + headers;

// Variable to store deserialized JSON
StaticJsonDocument<1500> doc;

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
  // DESERIALIZE JSON DATA
  // Dates and temperatures for the next week
  JsonObject daily = doc["daily"];
  JsonArray days = daily["time"];
  JsonArray maxTemperatures = daily["temperature_2m_max"];
  JsonArray minTemperatures = daily["temperature_2m_min"];

  // Selected date
  const char* day = days[daysInAdvance];
  String date = String(day);

  // minimum and maximum temperatures
  float maxTemp = maxTemperatures[daysInAdvance];
  float minTemp = minTemperatures[daysInAdvance];

  //==============================================
  // PRINT DATA
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.setTextSize(2);

  // Coordinates
  M5.Lcd.println("Coordinates:");
  M5.Lcd.print(latitude);
  M5.Lcd.println(",");
  M5.Lcd.println(longitude);
  M5.Lcd.println();

  // Date
  M5.Lcd.println(date);
  M5.Lcd.println();

  // Temperature
  M5.Lcd.println("Min Temp:");
  M5.Lcd.println(minTemp);
  M5.Lcd.println("Max Temp:");
  M5.Lcd.println(maxTemp);
}

//============================================
// LOOP
void loop() {
}

//=======================================================
// MAKE API GET REQUEST FUNCTION
// This function makes the API request using the url defined
// at the top of the sketch
void getData() {
  // set up HTTP Client
  HTTPClient client;

  // access URL
  client.begin(url.c_str());

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