//==============================================
// File:    M5StickCPlus_SendESPNOW
//
// Author:  J. Hathway
//
// Description:
//     - Send incoming ESP NOW messages on 
//       button press
//===============================================

#include <M5StickCPlus.h>
#include "M5Stick_ESPNOW.h"

// Message to send
// ***MUST be same data type as receiver
int counter = 0;

void setup()
{
    // initialise M5Stick
    M5.begin();

    // initialise ESPNOW send
    espInitSend();

    // MAC addresses to send to
    uint8_t macAddress[] = {0x4C, 0x75, 0x25, 0x9F, 0x64, 0xF0};
    uint8_t macAddress2[] = {0x4C, 0x75, 0x25, 0x9F, 0x09, 0x28};

    // pair with MAC addresses
    sendTo(macAddress);
    sendTo(macAddress2);
}

void loop()
{   
    //================================================
    // HOME BUTTON
    // Counts up
    if (digitalRead(M5_BUTTON_HOME) == LOW)
    {
        // increment counter, print
        counter++;

        // clear screen
        M5.Lcd.setCursor(0, 0);
        M5.Lcd.fillScreen(BLACK);

        // send message
        // ***MUST specify data type
        M5.Lcd.println("Sending message:\n" + String(counter));
        espSend<int>(counter);

        // wait until button lifted
        while (digitalRead(M5_BUTTON_HOME) == LOW)
        {
        }
    }

    //================================================
    // RESET BUTTON (right side of screen)
    // Counts down
    if (digitalRead(M5_BUTTON_RST) == LOW)
    {
        // increment counter, print
        counter--;

        // clear screen
        M5.Lcd.setCursor(0, 0);
        M5.Lcd.fillScreen(BLACK);

        // send message
        // ***MUST specify data type
        M5.Lcd.println("Sending message:\n" + String(counter));
        espSend<int>(counter);

        // wait until button lifted
        while (digitalRead(M5_BUTTON_RST) == LOW)
        {
        }
    }
}
