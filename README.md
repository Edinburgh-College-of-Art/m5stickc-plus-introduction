# Getting Started with the M5StickC Plus

![](images/M5Stick_Hero.png)


## Contents
- [Introduction](#what-is-the-m5stickc-plus)
- [Onboard Components](#onboard-components)
- [Programming](#programming-options)
    - [Programming Languages](#supported-programming-languages)
    - [Choosing an IDE](#choosing-an-ide)
- [Wireless Communication](#wireless-communication)
    - [Wireless Options](#wireless-options)
    - [Communication Protocols](#communication-protocols)
    - [Cloud Services](#cloud-services)
- [Resources](#resources)
    - [M5Stack Examples](#m5stack-examples)
    - [Tutorial Videos](#tutorial-videos)
    - [Useful Links](#useful-links)


## What is the M5StickC Plus?

The M5StickC Plus is a compact development board created by [M5Stack](https://m5stack.com/). About the size of a thumb; it features an onboard ESP32-PICO-D4 microcontroller with built-in Wi-Fi and Bluetooth modules for wireless communication. 

This board ships with several in-built sensors and actuators and a prebuilt housing, ready for you to start programming straight out of the box.


## Onboard Components

![](images/M5Stick_BackAndFront.png)

The M5StickC Plus board ships with several onboard components ready to start programming. M5Stack also provides an Arduino library for using these components.

- 120mAh LiPo Battery
- [Red LED](/examples/Onboard-Components/LED/)
- [Two Programmable Buttons](/examples/Onboard-Components/Buttons/)
- [1.14" TFT LCD Display](/examples/Onboard-Components/LCD-Display/)
- [Passive Buzzer](/examples/Onboard-Components/Buzzer/)
- [6-Axis Inertial Measurement Unit (IMU)](/examples/Onboard-Components/IMU/)
- [Real-Time Clock (RTC) Module](/examples/Onboard-Components/RTC/)
- [SPI Flash File Storage (SPIFFS)](/examples/Onboard-Components/SPIFFS/)
- IR Transmitter
- Microphone
- [Wi-Fi Module](/examples/Wireless-Communication/Wi-Fi/)
- [Bluetooth Module](/examples/Wireless-Communication/Bluetooth/)

The M5StickC Plus also has three GPIO pins, 5V and 3V3 pins, and a Grove port for connecting even more devices.


## Programming Options
### Supported Programming Languages

The M5StickC Plus contains an ESP32 microcontroller chip that acts as the brains of the device. This chip can be programmed to control the on-board components, as well as devices connected to the GPIO/Grove port.

The M5Stick can be programmed using:

- [Arduino Framework](https://www.arduino.cc/)
- [UIFlow](https://flow.m5stack.com/)
- [MicroPython](http://micropython.org/)
- [.NET nanoFramework](https://github.com/nanoframework/nanoFramework.M5Stack)

For the purpose of these tutorials, we will be focusing on programming the M5StickC Plus using the C++ with Arduino framework, however, you can find out more about the other programming options by clicking the links above.

### Choosing an IDE

To start programming the M5Stick with Arduino framework, you will first need to decide what Integrated Development Environment (IDE) to use. This will be where you write your code and upload it to the M5Stick.

For most beginner applications, the [Arduino IDE](https://docs.arduino.cc/software/ide/) will be a perfectly suitable choice. However, if you would like to take advantage of various extensions and a slightly more professional programming environment, you may want to opt for the [PlatformIO](https://platformio.org/) extension for VS Code. 

**You will only need to choose one of these options to start programming your M5StickC Plus board.**

You can find tutorials here for installing setting up your IDE of choice:

- [Arduino IDE](examples/Getting-Started/ArduinoIDE_Setup/README.md)
- [PlatformIO](examples/Getting-Started/PlatformIO_Setup/README.md)


## Wireless Communication

The M5StickC Plus has in-built modules for Wi-Fi and Bluetooth. This allows us to send data wirelessly between devices locally or via an internet connection.

We can even pull data from APIs and log data wirelessly using dedicated cloud services.

### Wireless Options

- [Bluetooth Classic](/examples/Wireless-Communication/Bluetooth/)
- Bluetooth Low Energy (BLE)
- [Wi-Fi](/examples/Wireless-Communication/Wi-Fi/)

### Communication Protocols

- [APIs](/examples/Wireless-Communication/APIs/)
- [ESP-NOW](/examples/Wireless-Communication/ESP-NOW/)
- [OSC](/examples/Wireless-Communication/OSC/)

### Cloud Services

- [AdafruitIO](/examples/Cloud-Services/AdafruitIO/)
- [ThingSpeak](/examples/Cloud-Services/ThingSpeak/)


## Resources

### M5Stack Examples

The M5StickCPlus library contains examples that we can use to immediately start programming the M5StickC-Plus. These examples include sketches for using some of the M5Stick's onboard components, as well as some games that you can try out.

In the Arduino IDE, these examples can be found by navigating to *File > Examples > M5StickCPlus*.


You can also find these examples in the [M5StickCPlus library GitHub repo](https://github.com/m5stack/M5StickC-Plus).

### Useful Links

- [M5Stack Arduino Documentation](https://docs.m5stack.com/en/arduino/arduino_ide)
- [M5Stack API Documentation](https://docs.m5stack.com/en/arduino/m5stickc_plus/button)
- [PlatformIO](https://platformio.org/)

Sites like [RandomNerdTutorials.com](https://randomnerdtutorials.com/projects-esp32/) provide excellent ESP32 tutorials that should work with the M5StickC Plus
