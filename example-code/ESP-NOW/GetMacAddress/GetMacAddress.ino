#include <M5StickCPlus.h>
#include <WiFi.h>

void setup()
{
  M5.begin();
  Serial.begin(115200);

  M5.Lcd.setTextSize(2);
  M5.Lcd.setRotation(1);

  M5.Lcd.println("MAC Address:");
  M5.Lcd.println(WiFi.macAddress());

  Serial.println("MAC Address:");
  Serial.println(WiFi.macAddress());
}

void loop() {}