# ESP-NOW with M5StickC-Plus

- [ESP-NOW with M5StickC-Plus](#esp-now-with-m5stickc-plus)
	- [Introduction](#introduction)
	- [Setup](#setup)
	- [Code](#code)
		- [Dependencies](#dependencies)
        - [Sending Device](#sending-device) 
        - [Receiving Device](#receiving-device)
	    - [M5Stick_ESPNOW.h file](#m5stick_espnowh-file)
	- [Troubleshooting](#troubleshooting)

## Introduction
[ESP-NOW](https://www.espressif.com/en/solutions/low-power-solutions/esp-now) is a wireless communication protocol created by Espressif, which enables quick, direct communication between ESP boards (ESP8266, ESP32, ESP32-S and ESP32-C) without the need of a WiFi router. The M5StickC-Plus is built around the ESP32 development board and is able to utilise ESP-NOW to send messages from:

- one device to another device.
- one device to multiple other devices.
- multiple devices to a single device.
- a combination of the above.

It should be noted that this is a short range form of communication with a range in the open of approx. 200m (650ft).

## Setup
To start sending ESP-NOW messages between devices, you will need to know the MAC address of the device(s) you are sending to. There is an Arduino sketch in the example-code folder that will print the MAC address of your M5StickC-Plus to the on-board LCD screen. 

Alternately, copy and paste this code into an empty sketch and upload it to your M5StickC-Plus:

```cpp
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
```
The MAC address should look something like <code>4C:75:25:9E:A5:BC</code>. Keep a note of this as you will need it later.

## Code
### Dependencies
As with all M5StickC-Plus projects, you will need to install the [M5StickCPlus library](https://github.com/m5stack/M5StickC-Plus) from the Arduino Library Manager.

For this code, the operations for sending and receiving ESP-NOW messages have been abstracted into a header file for easier use. To include this in your project, you will need to download the <code>M5Stick_ESPNOW.h</code> file and copy it to you project's source folder. You will then need to include the following lines at the top of you code:

```cpp
#include <M5StickCPlus.h>
#include "M5Stick_ESPNOW.h"
```
### Sending Device
#### setup()
After initialising the M5StickC-Plus with the <code>M5.begin()</code> function, you can also initialise ESP-NOW with the <code>espInitSend()</code> function.

```cpp
// initialise M5Stick
M5.begin();

// initialise ESPNOW send
espInitSend();
```

You will need to specify which MAC address(es) you would like to send to. These addresses need to be stored in arrays of type <code>uint8_t</code> and written in hexidecimal notation for the <code>sendTo()</code> function to recognise them. 

```cpp
// MAC address of paired device
uint8_t macAddress[] = {0x4C, 0x75, 0x25, 0x9F, 0x64, 0xF0};

// pair with new device
sendTo(macAddress);
```

To send to multiple devices, we can just repeat the above example like so:

```cpp
// MAC addresses to send to
uint8_t macAddress[] = {0x4C, 0x75, 0x25, 0x9F, 0x64, 0xF0};
uint8_t macAddress2[] = {0x4C, 0x75, 0x25, 0x9F, 0x09, 0x28};
  
  // pair with new devices
sendTo(macAddress);
sendTo(macAddress2);
```

#### loop()
Once setup is completed, we can send messages using the template function <code>espSend()</code>. We will need to specify the variable type of the message we are sending in the angled brackets.

```cpp
espSend<String>("Hello world!");
delay(100);
```

It is useful to include a small delay between sending each message to allow time for the M5StickC-Plus to send the message, and to allow the paired device(s) to receive.

### Receiving Device
To set up the receiving device, we first need to create a variable at the top of the code that will store the incoming messages. It is crucial that this variable is the same type as the message being sent. If this is not the case, the receiving device will not be able to interperet the incoming messages correctly.

```cpp
String message = "";
```

#### setup()
After initialising the M5StickC-Plus with the <code>M5.begin()</code> function, you can also initialise ESP-NOW with the <code>espInitRcv()</code> function.

```cpp
// initialise M5Stick
M5.begin();

// initialise ESPNOW receive
espInitRcv();
```

You can then set up the message variable to receive any incoming messages. This works by copying the incoming message to the message variable each time a message is received. Because of this, you do not need anything in the <code>loop()</code> function to check for new messages.

```cpp
// copies received messages to input paramter
// ***MUST specify data type
espReceive<int>(message);
```

### M5Stick_ESPNOW.h file
The M5Stick_ESPNOW.h file contains some fucntions for sending ESP-NOW messages. It makes use of functions and objects provided in the [esp-idf library](https://github.com/espressif/esp-idf) (that is installed as a dependency of the [M5StickCPlus library](https://github.com/m5stack/M5StickC-Plus)) as well as the [Arduino WiFi library](https://github.com/arduino-libraries/WiFi) (comes preinstalled with the Arduino IDE). 

We can make use of these tools by including the following lines at the top of our code:

```cpp
#include <esp_now.h>
#include <WiFi.h>
```

### Pairing
To pair a device we can use the <code>esp_now_peer_info_t</code> object. We can use the <code>memcpy()</code> function to copy the MAC address to this object, and then use the <code>esp_now_add_peer()</code> function to register the device as a peer.

```cpp
// MAC address of paired device
uint8_t macAddress[] = {0x4C, 0x75, 0x25, 0x9F, 0x64, 0xF0};

// register peer device
esp_now_peer_info_t peerInfo;
memcpy(peerInfo.peer_addr, macAddress, 6);
esp_now_add_peer(&peerInfo)
```

Before carrying on we will also need to set the WiFi object to station mode.

```cpp
WiFi.mode(STA);
```

### Sending
We are given the option to register a callback function that will be called everytime we send a message. We can use this to print a message to tell us if the message was not delivered.

```cpp
// function called when message is sent
esp_now_register_send_cb(
    [](const uint8_t *mac_addr,esp_now_send_status_t status) {
        if (_status != ESP_NOW_SEND_SUCCESS)
            M5.Lcd.println("Failed to deliver");
    });
```
Finally, we are able to send our message with the <code>esp_now_send()</code> function.

```cpp
int message = 1;
esp_now_send(0, (uint8_t *)&message, sizeof(message));
```
### Receiving 
We will need to register a callback function that will be called everytime we receive a message. This code uses the callback function to copy the incoming data to the address of a variable.

```cpp
int message;

// function called when receive is registered
esp_now_register_recv_cb(
    [](const uint8_t *_mac, const uint8_t *incomingData, int len) {
        memcpy(&message, incomingData, sizeof(message));
    });
```

## Troubleshooting
- Message not received and "Failed to deliver message" appears?
    - Make sure the MAC address is correct and entered properly using the <code>sendTo()</code> function.
- Message IS received but "Failed to deliver message" still appears?
    - If you are sending to one device, make sure you have only entered one MAC address in the <code>setup()</code> function of the sending device. Likewise, if you are sending to multiple devices, make sure you only have the <code>sendTo()</code> function appear as many times as you have receiving devices (e.g. 3 devices require 3 MAC addresses).
- Message received but is just printing random characters?
    - The message you are sending needs to be the same type as the message you receive. If you send a String, you must receive a String; if you send an integer, you must receive an integer etc.
- "Error initializing ESP-NOW"
    - device is unable to initialise connection. Restart device.
