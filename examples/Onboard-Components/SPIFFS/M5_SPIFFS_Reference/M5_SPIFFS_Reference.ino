//=============================================================
// File:    M5_SPIFFS_Reference.ino
//
// Author:  J. Hathway 2024
//
// Dependencies:
//     - M5StickCPlus library (M5Stack)
//
// Description:
//     - This sketch uses methods from the SPIFFS library to 
//       write, read, append, and remove files from SPIFFS.
//=============================================================

#include <M5StickCPlus.h>
#include <SPIFFS.h>

String filename = "/test.txt";
  
void setup() {
    // Initialise M5Stick & Serial Monitor
    M5.begin();
    Serial.begin(115200);
    
    //=============================================
    // Start SPIFFS
    while (!SPIFFS.begin()) {
        Serial.println("Failed to start SPIFFS. Retrying in 3 seconds...");
        delay(3000);
    }

    //=============================================
    // Check if file exists
    if (!SPIFFS.exists(filepath)) {
        Serial.println("File exists\nReady to overwrite...")
    }

    //=============================================
    // Format SPIFFS
    Serial.println("Formatting...");
    SPIFFS.format(); 

    //=============================================
    // Write new file
    Serial.print("Opening file: ");
    Serial.println(filename);

    // Open file in "write" mode
    File file = SPIFFS.open(filename, "w");

    if (file) {
        Serial.print("Writing to file...");
        file.print("Hello World!"); // write "Hello World!" to file
        file.close(); // close file
    } else {
        Serial.println("Unable to open file");
    }

    Serial.println("Done.");

    //=============================================
    // Append data to file
    Serial.print("Opening file: ");
    Serial.println(filename);

    // Open file in "append" mode
    File file = SPIFFS.open("test.txt", "a");

    if (file) {
        Serial.print("Appending data to file...");
        file.print("Ahoy!"); // write "Hello World!" to file
        file.close(); // close file
    } else {
        Serial.println("Unable to open file");
    }

    Serial.println("Done.");

    //=============================================
    // Read file
    Serial.print("Opening file: ");
    Serial.println(filename);

    // Open file in read mode
    File file = SPIFFS.open("test.txt", "r");   

    String data = ""; // variable for storing data

    if (file) {
        Serial.print("Reading file...")
        // Read contents to data
        for (int i = 0; i < file.size(); i++)
            data += (char)file.read();

        file.close(); //close file
    } else {
          Serial.println("Unable to open file");
    }

    Serial.println("Done.");

    // Print data to serial monitor
    Serial.println(data);

    //=============================================
    // Remove file
    Serial.print("Removing file: ");
    Serial.println(filename);

    // Remove file from SPIFFS
    SPIFFS.remove("test.txt");

    Serial.println("Done.");
}

void loop() {}