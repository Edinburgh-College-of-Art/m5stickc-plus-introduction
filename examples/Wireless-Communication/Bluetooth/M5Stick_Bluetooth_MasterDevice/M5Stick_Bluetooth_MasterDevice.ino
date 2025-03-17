//=============================================================
// File:    M5Stick_Bluetooth_MasterDevice.ino
//
// Author:  J. Hathway 2025
//
// Dependencies:
//     - M5StickCPlus library (M5Stack)
//
// Description:
//     - This sketch will initialise the M5Stick as a Bluetooth
//       master device.
//     - Once connected to the slave device, it will send and 
//       receive messages over Bluetooth Serial.
//=============================================================

#include <M5StickCPlus.h>
#include <BluetoothSerial.h>

// Create Bluetooth Serial object
BluetoothSerial bluetooth;

// Define master and slave device names
String masterDevice = "M5Stick_Master";
String slaveDevice = "M5Stick_Slave";

// This message will be sent to the slave device when connected
// Feel free to change it (please be polite)
String messageOut = "Greetings";

void setup() {
  // Initialise...
  M5.begin();            // ...M5Stick
  Serial.begin(115200);  // ...Serial monitor - for debugging
  Serial.println();

  // Start Bluetooth Serial
  // "true" argument sets this device to be master device
  bluetooth.begin(masterDevice, true);
  Serial.println(masterDevice + " Bluetooth Serial started.");

  Serial.println("Connecting to " + slaveDevice + "...");
  
  // Wait until connected to slave device
  while (!bluetooth.connect(slaveDevice)) {}

  // Send message to Serial monitor to confirm connection
  Serial.println("Connected to " + slaveDevice);
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
