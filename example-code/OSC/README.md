# Open Sound Control (OSC) with M5StickC-Plus

## Contents
- [Introduction](#introduction)
- [Key Features](#key-features)
- [Setting up](#setting-up)
- [Examples](#examples)

## Introduction
[Open Sound Control (OSC)](https://opensoundcontrol.stanford.edu/) is a communication protocol developed at UC Berkeley for real-time message exchange between software applications and hardware. Originally created for low-latency communication, it was specifically designed for use in real-time musical performance. OSC has now expanded beyond just sound applications and is used in a variety of real-time interactive applications.

OSC messages are made up of a few components:
1. Address: each OSC message is sent with an address which allows us to route data to the relevant areas in our code/programs.
2. Value: the contents of the message. This can be integer, float or string values.

For example : <code>/M5Stick/Buttons/ButtonA 1</code> has an address of <code>/M5Stick/Buttons/ButtonA</code> and a value of <code>1</code>.

These messages can then be transported over local networks via USP (User Datagram Protocol) packets or bundles.

## Key Features
- **Real-time Communication**: OSC is designed for fast and efficient communication between different devices and software applications in real-time scenarios.
- **Flexible Message Format**: Messages in OSC are represented as bundles or individual packets containing addresses and corresponding data values, allowing for flexible and structured communication.
- **Cross-Platform**: OSC is platform-independent, making it suitable for use across various operating systems and hardware configurations.
- **Scalability**: It supports various data types, enabling the transmission of diverse types of information such as MIDI data, sensor readings, and control commands.

## Setting Up
To start sending/receiving OSC messages using the M5Stick, you will first need to install the [OSC library by Adrian Freed](https://github.com/CNMAT/OSC). This contains all the necessary functions for sending OSC messages. 

In your code, you will need to connect your M5Stick to your local Wi-Fi network. You can see how to do this [here](../WiFi/). You will also need to specify the IP address and network port of the device you are sending to:

1. IP Address is provided to each device on a network by the network router and should look something like <code>10.192.4.96</code>. The IP address of a device can be found by:
    - [**Windows**] navigating to **Start > Settings > Network & Internet > Wi-Fi** and selecting the Wi-Fi network you are on. Under **Properties**, your IP address should be listed next to **IPv4 address**. 
    - [**Mac**] opening the **Apple Menu** and opening **System Settings**. From there, navigate to **Network > Wi-Fi > Details** and your IP address should be listed next to **IP address**.
    - [**Another M5Stick**] creating a sketch to [connect to your local Wi-Fi network](../WiFi/ConnectToWiFi/ConnectToWiFi.ino). You can then print the M5Stick's IP address to the LCD display using the line <code>M5.Lcd.print(WiFi.localIP());</code>.

2. The network port is the port your receiving device is listening on. It is a logical connection that is used by programs and services to exchange information. These ports are represented by an integer number between 0-65535.
    - Ports 0-1023 are usually taken by other communication services, such as HTTP and HTTPS (ports 80 and 443 respectively) so you should **only make use of any ports between 1024-65535 for sending OSC messages**.
    - It is important that the receiving device is listening to the same port that the sending device is sending to.

## Examples
- [Basic OSC Send](BasicOSCSend/BasicOSCSend.ino)
- [Basic OSC Receive](BasicOSCReceive/BasicOSCReceive.ino)
- [Send Int Data](SendInt_Counter/SendInt_Counter.ino)
- [Send Float Data](SendFloat_IMU/SendFloat_IMU.ino)
- [Send String Data](SendTxt_HelloWorld/SendTxt_HelloWorld.ino)