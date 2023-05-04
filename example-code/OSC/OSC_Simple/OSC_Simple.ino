//==============================================
// OSC_Simple example
//
// Send a message via OSC every 15ms
//==============================================

#include <M5StickCPlus.h>

#include "M5Stick_OSC.h"
#include "M5Stick_WiFi.h"

//=============================================
// **CHANGE THESE VARIABLES**
const char *network = "YourNetworkName";
const char *password = "YourPassword";

const char *ip = "10.126.204.251";
const unsigned int port = 8000;

//=============================================
// GLOBAL VARIABLES
int message = 0;

//=============================================
// SETUP
void setup()
{
    // initialise M5Stick
    M5.begin();

    // connect to network
    connectToWifi(network, password);

    // IP address and port to send to
    sendTo(ip, port);
}

//=============================================
// LOOP
void loop()
{
    // send OSC message
    sendOscMessage<int>("/m5stick", message);

    // perform the loop every 15 ms
    // this may be too fast for some routers to enjoy themselves
    // so set it to something less if you need to
    delay(27);
}