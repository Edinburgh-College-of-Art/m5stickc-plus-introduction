# M5StickC Plus Built-in Buzzer

![](images/Thumbnail_M5Stick_Buzzer.png)

## Contents

- [Introduction](#introduction)
- [Controlling the Buzzer](#controlling-the-buzzer)
    - [Start Buzzer](#start-buzzer)
    - [Stop Buzzer](#stop-buzzer)

## Introduction
The M5StickC Plus ships with a passive buzzer among its onboard components. A buzzer can be a really useful component for adding sonic feedback to your projects. 

There are two main types of buzzer we can use in our electronics projects:

- **active** - produce a sound when directly powered.
- **passive** - requires a input trigger wave to produce sound.

As a result of these characteristics, active buzzers can only produce a single frequency tone, whereas passive buzzers can produce various frequency tones based on the input wave.

This usually requires a bit of extra programming to achieve, however the M5StickC Plus library provides us with some simple-to-use methods for controlling the onboard buzzer's frequency and volume.

## Controlling the Buzzer
The M5StickC Plus library provides some class methods for more easily controlling the buzzer on the M5StickC Plus board.

To make use of these methods, we need to include the M5StickC Plus library in the project sketch and the line <code>M5.begin()</code> in the <code>setup()</code> function.

``` cpp
#include <M5StickCPlus.h>

void setup() {
    M5.begin();
}
```

To see a full example sketch, [click here](M5_Buzzer_Beep/M5_Buzzer_Beep.ino).

### Start buzzer
We can  use <code>M5.Beep.tone()</code> to start a tone at a defined frequency.

``` cpp
M5.Beep.tone(440); // start a 440Hz tone (A4 on a piano)
```

### Stop buzzer
Then to turn off the beep, we use the <code>M5.Beep.mute()</code> method.

``` cpp
M5.Beep.mute();
```