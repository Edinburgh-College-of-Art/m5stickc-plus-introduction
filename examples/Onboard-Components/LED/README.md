# M5StickC Plus Built-in LED

![](images/Thumbnail_M5Stick_LED.png)

## Contents

- [Introduction](#introduction)
- [Blink Sketch](#blink-sketch)
    - [Code](#code)
    - [How it Works](#how-it-works)

## Introduction
As with most electronics prototyping boards, the M5StickC Plus comes with a built-in red LED that we can control using some code. 

Learning how to control a built-in LED can be a good way to start combining your code and hardware, and is generally considered the “Hello World” of  electronics programming.

The LED can also provide some simple visual feedback in our projects. This could be a flash to let us know the M5Stick has received a message, or programming a pattern of flashes to tell us it has paired successfully with another device.

The LED on the M5StickC Plus is connected internally to GPIO 10, and we can turn it on/of using a little bit of code.

## Blink Sketch
One of the first things we usually do with a new electronic prototyping board is make the builtin LED blink on and off periodically. This is a very simple way of checking that the software and hardware are working together as expected. It can also raise issues with the board before we start doing anything more complicated.

### Code 
You can find the full example sketch [here](M5StickCPlus_LED_Blink/M5StickCPlus_LED_Blink.ino).

### How it works
First of all we should include the M5StickC Plus library. Although not strictly necessary here as we aren't using any classes/functions from the library, some IDEs will not compile code for the M5Stick if it is not included.

We will be using GPIO pin 10 to control the LED as it is connected internally. As such, we will store this pin number as a variable for use later. 

``` cpp
#include <M5StickCPlus.h>

// Pin 10 is connected to the built-in LED
const int ledPin = 10;
```

In the <code>setup()</code>, we use the <code>pinMode()</code> function to initialise the led pin as an <code>OUTPUT</code> as we will be sending it a signal - and are not expecting to read from this pin.

``` cpp
pinMode(ledPin, OUTPUT);
```

Lastly, we can use <code>digitalWrite()</code>  to send <code>HIGH</code> and <code>LOW</code> signals to the led, turning it on and off respectively. In between, we also use the <code>delay()</code> function to provide a 1000 millisecond delay between each LED change.

``` cpp
// Turn on LED for 1 second
digitalWrite(ledPin, HIGH);
delay(1000);
  
// Turn off LED for 1 second
digitalWrite(ledPin, LOW);
delay(1000);
```