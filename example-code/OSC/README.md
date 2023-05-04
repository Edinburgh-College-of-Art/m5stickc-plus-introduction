# Sending OSC Messages with M5StickC-Plus

- [Sending OSC Messages with M5StickC-Plus](#sending-osc-messages-with-m5stickc-plus)
	- [Introduction](#introduction)
	- [Setup](#setup)
	- [Code](#code)
		- [Dependencies](#dependencies)
        - [Variables](#starting-variables)
	    - [M5StickOSC.h file](#m5stickosch-file)
	- [Troubleshooting](#troubleshooting)

## Introduction

[Open Sound Control (OSC)](http://opensoundcontrol.org), like MIDI, is standard for interpreting data sent over a network for control over audio devices and software.

[Video tutorial available on Media Hopper](https://media.ed.ac.uk/media/Sending+OSC+Messages+with+M5StickC+Plus/1_jm4bpf9v)

## Setup

To send OSC messages, we need to specify a couple of things. 

First of all, we need the IP address of the device we are sending to. To find your computer's IP addres, open the terminal/command prompt, and input <code>ipconfig</code>. This should return some information about your device's network configuration, including its IP address.

```py
IPv4 Address. . . . . . . . . . . : 10.126.204.251
```
You will also need to set a TCP port number that you want to send to. This is usually in the range of 1024-65536. Numbers below 1024 are usually reserved for other services.

## Code
### Dependencies
This code makes use of two header files to carry out the operations needed to send OSC messages. <code>M5StickOSC.h</code> provides functions that allow us to send OSC messages, and <code>M5StickWiFi.h</code> contains a function for connecting to a WiFi network. 

Abstracting this code into header files both cleans up the code and allows useful functions to be easily shared across multiple projects. To include them in your projects, you will need to copy and paste the files into your project's source folder, and include the following lines at the top of your code:

```cpp
#include "M5StickOSC.h"
#include "M5StickWiFi.h"
```

This code also requires the [OSC library by Adrian Freed and Yotam Mann](https://github.com/CNMAT/OSC) alongside the [M5StickCPlus library by M5Stack](https://github.com/m5stack/M5StickC-Plus). You can install both of these libraries through the Arduino library manager.

### Starting Variables
In this code, there are some details that you will need to fill in.

Your WiFi network details...

```cpp
const char *network = "YourNetworkName";
const char *password = "YourPassword";
```

...as well as the IP address of the device you are sending to, and the TCP port number you are sending to.

```cpp
const char *ip = "10.126.176.199";
const unsigned int port = 8000;
```
Note: if you set the IP address to xxx.xxx.xxx.255 [changing the 'x's to match your IP address], this will send to all devices on that network. This is known as the broadcast address of a network.

### setup()
The <code>M5StickOSC.h</code> file gives us the function <code>sendTo()</code> to set the IP address and port we want to send to. We will also want to connect to a WiFi network using the <code>connectToWifi()</code> function from the <code>M5StickWiFi.h</code> file. These operations will only need to happen once, so they can be called in the <code>setup()</code> function.

```cpp
// connect to network
connectToWifi(network, password);

// IP address and port to send to
sendTo(ip, port);
```

### loop()
Once setup is complete, sending OSC messages can be done using the template function <code>sendOscMessage()</code>. This takes in the route we want to send to as well as the message we are sending as input parameters. 

You will also need to specify the variable type of the message you are sending inside the angled brackets.

```cpp
sendOscMessage<int>("/m5stick", 1);
```

### M5StickOSC.h file
The <code>M5StickOSC.h</code> header file abstracts the operations required for sending OSC messages into functions to clean up the main body of code and make it easier to organise. If we wanted to send OSC messages without this header file, there are a couple of steps we need to follow.

First we need to include some header files from the [OSC library](https://github.com/CNMAT/OSC). 

```cpp
#include <WiFiUdp.h>
#include <OSCMessage.h>
#include <OSCBundle.h>
#include <OSCData.h>
```

We then need to create instances of two objects: the OSCMessage class for creating our messages, and the WiFiUDP class for carrying the OSC messages. The OSCMessage object requires the route as a constructor argument.

```cpp
WiFiUDP udp;
OSCMessage oscMsg("/m5stick");
```

We are then able to create a message (in this case we are sending the variable <code>message</code>) and send it via UDP...

```cpp
// create message
oscMsg.add(0);   

// send message
udp.beginPacket(udpAddress, udpPort);
oscMsg.send(udp);
```
...and clean up the message, ready for the next one.

```cpp
// clear message
udp.endPacket(); 
oscMsg.empty();  
```

## OSC to Max 8
To receive OSC messages in Max 8, we can use the <code>udpreceive 8000</code> object, with the port number we want to listen to as an argument.

Incoming messages can then be filtered using the <code>route</code> object, with the routes of the incoming messages used as arguments.

e.g. <code>route /pitch /roll /yaw</code>

![](https://github.com/Edinburgh-College-of-Art/m5stickc-plus-introduction/blob/main/images/Max8_OSCpatch.PNG)

### Troubleshooting

There are a few reasons for no data arriving, check through the following

- Is the IP address correct?
    - Try setting the IP in the Arduino sketch to your machine's IP rather than broadcasting
- is the M5Stick Connected to WiFi?
    - The M5Stick will print its WiFi status after startup
- Is the port correct?
    - Make sure the port specified in Arduino sketch matches the port number on the <code>udpreceive</code> object
