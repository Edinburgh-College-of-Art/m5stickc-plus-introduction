//=============================================================
// File:    M5Stick_Bluetooth_SlaveDevice.ino
//
// Author:  J. Hathway 2025
//
// Dependencies:
//     - M5StickCPlus library (M5Stack)
//
// Description:
//     - This sketch will initialise the M5Stick as a Bluetooth
//       slave device.
//     - Once connected to the master device, it will send and 
//       receive messages over Bluetooth Serial.
//=============================================================

#include <M5StickCPlus.h>
#include <BluetoothSerial.h>

// Create Bluetooth Serial object
BluetoothSerial bluetooth;

// Define slave and master device names
String slaveDevice = "M5Stick_Slave";

// This message will be sent to the master device when connected
// Feel free to change it (please be polite)
String messageOut = "Hello";

void setup() {
  // Initialise...
  M5.begin();            // ...M5Stick
  Serial.begin(115200);  // ...Serial monitor - for debugging
  Serial.println();

  // Start Bluetooth Serial
  // "false" argument sets this device to be slave device
  bluetooth.begin(slaveDevice, false);
  Serial.println(slaveDevice + " Bluetooth Serial started.");

  Serial.print("Waiting for Master device");

  // Wait until connected to master device
  while (!bluetooth.connected()) {
    Serial.print(".");
    delay(500);
  }

  // Send message to Serial monitor to confirm connection
  Serial.println();
  Serial.println("Connected");
}

void loop() {
  //=========================================================
  // SEND BLUETOOTH DATA

  // Send message
  bluetooth.print(messageOut);

  // Print to Serial monitor to confirm message sent
  Serial.println("Sent: " + messageOut);


  //=========================================================
  // RECEIVE BLUETOOTH DATA

  // Check for any incoming messages
  if (bluetooth.available()) {
    // Convert to String
    String messageIn = "";
    while (bluetooth.available())
      messageIn += char(bluetooth.read());

    // Print incoming message
    Serial.print("Received: ");
    Serial.println(messageIn);
  }

  // Short delay before looping
  delay(1000);
}
