# ESP-NOW with M5StickC-Plus

![](images/Thumbnail_M5Stick_ESPNOW.png)

## Contents
- [Introduction](#introduction)
    - [MAC Addresses](#mac-addresses)
    - [Finding a MAC Address](#finding-a-mac-address)
- [Usage](#usage)
    - [Send](#sending-esp-now-messages)
    - [Receive](#receiving-esp-now-messages)

## Introduction
[ESP-NOW](https://www.espressif.com/en/solutions/low-power-solutions/esp-now) is a wireless communication protocol created by Espressif, which enables quick, direct communication between ESP boards (ESP8266, ESP32, ESP32-S and ESP32-C) without the need of a Wi-Fi router. The M5StickC-Plus is built around the ESP32 development board and is able to utilise ESP-NOW to send messages from:

- one device to another device.
- one device to multiple other devices.
- multiple devices to a single device.
- a combination of the above.

It should be noted that this is a short range form of communication with a range in the open of approx. 200m (650ft).

### MAC Addresses
ESP-NOW does not need a connection to Wi-Fi in order to send messages between devices. Instead, we require the MAC address of the device we want to send to.

A Media Access Control (MAC) address is a unique identifier assigned to electronic devices to distinguish them on a network. Unlike an IP address that is assigned to a device by the network router each time it connects to a network, MAC addresses are permanent addresses that are unique to each device no matter when, where, or if it is connected to a network.

In terms of ESP-NOW, we can imagine a device's MAC address as acting like a phone number; sending a message to a device requires using the receiving device's MAC address as a means of directly identifying and communicating with it.

### Finding a MAC address
For the full example sketch, [click here](M5_ESPNOW_GetMacAddress/M5_ESPNOW_GetMacAddress.ino).

As we require the MAC address of a device in order to send it ESP-NOW messages, we need a way of finding the MAC address of our M5StickC Plus boards. Luckily we can run some simple code to find and display the MAC address of a given M5Stick. 

You can upload the following code to your M5Stick to display its MAC address to the serial monitor and LCD display.

``` cpp
#include <M5StickCPlus.h>
#include <WiFi.h>
  
void setup() {
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

After uploading this code to your device, make sure to keep a note of what the MAC address is - from the serial monitor or LCD display - to use later. It should look something like this:

```
4C:75:25:9F:00:A8
```

## Usage
To send/receive ESP-NOW messages, we will need to include the following libraries at the top of the project sketch:

- **M5StickC Plus library** - for M5StickC Plus functions.
- **WiFi library** - to make use of the M5Stick's Wi-Fi antenna.
- **ESP-NOW library** - to make use of the ESP-NOW functions.

``` cpp
#include <M5StickCPlus.h>
#include <WiFi.h>
#include <esp_now.h>
```

### Sending ESP-NOW Messages
For the full example sketch, [click here](M5_ESPNOW_Send/M5_ESPNOW_Send.ino).

For sending ESP-NOW messages, we need to create some global variables in the space above the <code>setup()</code> function. These variables will store information about the device(s) we are sending to.

``` cpp
esp_now_peer_info_t peerInfo;
int peerCount = 0;
```

Inside the <code>setup()</code> function, we can first use <code>M5.begin()</code> to initialise the M5Stick and set the device to “Wi-Fi Station” mode. This will give us access to the Wi-Fi antenna inside the M5Stick.

``` cpp
void setup() {
  // Initialise M5Stick
  M5.begin();
​
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  
  ...
```

We can now initialise ESP-NOW using the <code>esp_now_init()</code> function. We will use an <code>if()</code> and a <code>while()</code> statement to make sure the code does not continue unless ESP-NOW has been initialised successfully. 

``` cpp
if (esp_now_init() != ESP_OK) {
  M5.Lcd.println("Error initializing ESP-NOW");
  while (true) {}
}
```

The next step involves pinning a callback function to be executed when a message is sent. At the bottom of the sketch, we have created a function called <code>callbackFunction()</code>. In here, we can define what happens when a message is sent.

For this example, we will just print a few messages to the M5Stick's LCD display to tell us what has been sent and if it was successful, but you can have anything you want to happen when a message is sent happen in here.

``` cpp
void callbackFunction(const uint8_t *_mac_addr, esp_now_send_status_t _status) {
  // Clear display
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
​
  M5.Lcd.println("Sending message:");
  M5.Lcd.println(outgoingMsg);
​
  // Check if message was delivered
  if (_status != ESP_NOW_SEND_SUCCESS) {
    M5.Lcd.println("Error: Failed to deliver.");
  } else {
    M5.Lcd.println("Delivered.");
  }
}
```

Back in the <code>setup()</code> function, we can pin this task to be executed when a message is sent using <code>esp_now_register_send_cb()</code> and pass the callback function as a function argument. 

We can also set the channel and encryption methods for our messages. For now we will use channel 0 and no encryption.

``` cpp
// callbackFunction() executed when message is sent
esp_now_register_send_cb(callbackFunction);
​
// register peer
peerInfo.channel = 0;
peerInfo.encrypt = false;
```

To pair a device, we need to store its MAC address. We will store the MAC address as an array of hexadecimal values. Each value in the MAC address should be separated by a comma, and prefixed with <code>0x</code> to denote it as a hexadecimal value.

If you want to send to multiple devices, you should create separate variables to store each device's MAC address. 

``` cpp
uint8_t macAddress[] = { 0x4C, 0x75, 0x25, 0x9E, 0x9F, 0xF4 };
//uint8_t macAddress2[] = { 0x4C, 0x75, 0x25, 0x9F, 0x09, 0x28 };
```

Now to pair the device(es) we will pass the MAC address of each device into a function we have created called <code>sendTo()</code>. This function is defined just below the <code>loop()</code> function and adds a MAC address to the list of addresses to send to.

Again, if you are sending to multiple devices, you will need to call this function once for every device you are sending to in order to pair the MAC address of each device.

``` cpp
sendTo(macAddress);
//sendTo(macAddress2);
```

In the <code>loop()</code> function, we can start sending ESP-NOW messages. In this example, we will attempt to send the outgoingMsg once every 10 seconds.

We do this by using the <code>esp_now_send()</code> function, which requires three arguments:

- **broadcast address** - will be 0 here as we are sending to all paired devices.
- **outgoing message reference** - a pointer to the outgoingMsg variable.
- **outgoing message size** - the size (in bytes) of the outgoing message.
 
If you are unfamiliar with any of these terms, just make sure to replace <code>outgoingMsg</code> with the variable that you want to send.

We will store the output of this function using a special <code>esp_err_t</code> variable.

``` cpp
esp_err_t result = esp_now_send(0, (uint8_t *)&outgoingMsg, sizeof(outgoingMsg));
```

Lastly, we can use the output of <code>esp_now_send()</code> to check if the message was sent successfully.

``` cpp
if (result != ESP_OK) {
  M5.Lcd.println("Error: Message not sent.");
}
```

### Receiving ESP-NOW Messages
For the full example sketch, [click here](M5_ESPNOW_Receive/M5_ESPNOW_Receive.ino).

To receive an ESP-NOW message, we must first create a global variable to store the incoming messages.For these examples, it is important that this is a string variable. Be aware, however, that this variable can be any type you need, just as long as it matches the type of the data being sent. In this example, we will use a string variable so that we can capture any message with a basic data type (i.e. int, float, String).

``` cpp
String incomingMsg = "";
```

Inside the <code>setup()</code> function, we can first use <code>M5.begin()</code> to initialise the M5Stick and set the device to “Wi-Fi Station” mode. This will give us access to the Wi-Fi antenna inside the M5Stick.

``` cpp
void setup() {
  // Initialise M5Stick
  M5.begin();
​
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  
  ...
```

We can now initialise ESP-NOW using the <code>esp_now_init()</code> function. We will use an <code>if()</code> and a <code>while()</code> statement to make sure the code does not continue unless ESP-NOW has been initialised successfully. 

``` cpp
if (esp_now_init() != ESP_OK) {
  M5.Lcd.println("Error initializing ESP-NOW");
  while (true) {}
}
```

The next step involves pinning a callback function to be executed when a message is received. At the bottom of the sketch, we have created a function called <code>callbackFunction()</code>. In here, we can define what happens when a message is received.

For this example, we will just print a few messages to the M5Stick's LCD display to tell us what has been received and if it was successful, but you can have anything you want to happen when a message is receive happen in here.

To read all of the incoming data, we need to use a <code>for()</code> loop to parse each character in the incoming data into the incomingMsg string variable. If we read a character equal to \0, that means the message is finished and we can exit the <code>for()</code> loop.

``` cpp
void callbackFunction(const uint8_t *_mac_addr, const uint8_t *_incomingData, int _len) {
  // Clear string variable
  incomingMsg = "";
​
  // Copy incoming data to message variable
  for (int i = 0; i < _len; i++) {
    // If end of strink, break loop
    if ((char)_incomingData[i] == '\0') {
      break;
    }
​
    incomingMsg += (char)_incomingData[i];
  }
​
  // Print message to LCD display
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.printf("New Msg:\n%s", incomingMsg);
}
```

Back in the <code>setup()</code> function, we can pin this task to be executed when a message is using <code>esp_now_register_vcer_cb()</code> and pass the callback function as a function argument.

``` cpp
esp_now_register_recv_cb(callbackFunction);
```

And with that, this code should read and print any incoming ESP-NOW messages to the M5Stick's LCD display. 

Because all the code we want to happen when the message is received is inside <code>callbackFunction()</code> and will be executed when a message is received, the <code>loop()</code> function can stay empty.