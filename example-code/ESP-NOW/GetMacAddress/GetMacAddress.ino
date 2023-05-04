#include <M5StickCPlus.h>
#include <WiFi.h>

#define PRINT_LN(x) M5.Lcd.println(x)

void setup()
{
  M5.begin();

  M5.Lcd.setTextSize(2);
  M5.Lcd.setRotation(1);

  PRINT_LN("MAC Address:");
  PRINT_LN(WiFi.macAddress());
}

void loop() {}