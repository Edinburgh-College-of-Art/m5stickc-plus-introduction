# M5StickC Plus Built-in Real-Time Clock (RTC)

![](images/Thumbnail_M5Stick_RTC.png)

## Contents
- [Introduction](#introduction)
- [Usage](#usage)
    - [Time](#time)
    - [Date](#date)
    - [Get time from API](#get-time-from-api)

## Introduction
A Real-Time Clock (RTC) - as the name suggests - is an electronic component that can keep an accurate track of time. The RTC's primary function is to keep track of time accurately over extended periods. It is optimized for low power consumption and high precision timekeeping.

The M5StickC Plus board contains an RTC (BM8563) chip that we can refer to for an accurate time reading. This can be useful for projects that require some sort of time/date keeping or for synchronising with other devices.

In order to use the RTC on the M5Stick, we can use some methods provided to use by the M5StickC Plus library to first set, then read the current time and date.

## Usage
The M5StickC Plus library provides us with several methods for setting and retrieving the time/date on the RTC module. 

As always when using the onboard components on the M5StickC Plus, the project sketch will need to include the M5StickC Plus library at the top, and <code>M5.begin()</code> inside the <code>setup()</code> function.

``` cpp
#include <M5StickCPlus.h>

void setup() {
  // Initialise M5Stick
  M5.begin();

  ...
```

### Time
The RTC module keeps track of the passage of time, however, we will need to set the time first. We can set and read the time using some methods given to us in the M5StickC Plus library.

To set the time, we first need to set up an <code>RTC_TimeTypeDef</code> object. This will store the time values. It is best to do this in the global space - above the <code>setup()</code> function - so that we can access it globally.

``` cpp
#include <M5StickCPlus.h>

RTC_TimeTypeDef TimeStruct;
```

Then inside the <code>setup()</code> function, we can set the initial hour, minute, and second values. To set this as the initial time, we then pass a reference to the <code>RTC_TimeTypeDef</code> object into the <code>M5.Rtc.SetTime()</code> method.

``` cpp
void setup() {
    M5.begin();

    TimeStruct.Hours = 12;
    TimeStruct.Minutes = 0;
    TimeStruct.Seconds = 0;
    M5.Rtc.SetTime(&TimeStruct);
}
```

The RTC will now keep an accurate track of the time. To access it, we first pass a reference to the <code>RTC_TimeTypeDef</code> object into the <code>M5.Rtc.GetTime()</code> method, and then read the values inside the  <code>RTC_TimeTypeDef</code> object.

``` cpp
// Get time
M5.Rtc.GetTime(&TimeStruct);

// Read time
int hour = TimeStruct.Hours;
int min = TimeStruct.Minutes;
int sec = TimeStruct.Seconds;
```

For a full example sketch, [click here](M5_RTC_Time/M5_RTC_Time.ino).

### Date
As well as keeping track of time, the M5.RTC class in the M5StickC Plus library allows us to keep an accurate track of the date, month, and year.

To set the date, we first need to set up an <code>RTC_DateTypeDef</code> object. This will store the date values. It is best to do this in the global space - above the <code>setup()</code> function - so that we can access it globally.

``` cpp
#include <M5StickCPlus.h>

RTC_DateTypeDef DateStruct;
```

Then inside the <code>setup()</code> function, we can set the initial date, month, and year values. To set this as the initial date, we then pass a reference to the <code>RTC_DateTypeDef</code> object into the <code>M5.Rtc.SetDate()</code> method.

``` cpp
void setup() {
    M5.begin();

    DateStruct.Date = 14;
    DateStruct.Month = 5;
    DateStruct.Year = 1966;
    M5.Rtc.SetDate(&DateStruct);
}
```

The RTC will now keep an accurate track of the date. To access it, we first pass a reference to the <code>RTC_DateTypeDef</code> object into the <code>M5.Rtc.GetDate()</code> method, and then read the values inside the  <code>RTC_DateTypeDef</code> object.

``` cpp
// Get date
M5.Rtc.GetDate(&DateStruct);

// Read date
int date = DateStruct.Date;
int month = DateStruct.Month;
int year = DateStruct.Year;
```

For a full example sketch, [click here](M5_RTC_Date/M5_RTC_Date.ino).

### Get Time from API
So far, we have covered how to set and read the time/date from the RTC chip on the M5Stick, however, they have both required manually setting the date at the start of the sketch. This means that you will have to change the time/date values every time you want to upload the code. As well as this, due to the variable delay between pressing ‘Upload’ and the code actually uploading, the time will probably no longer be accurate.

We can get around this by using an [API request](/examples/Wireless-Communication/APIs/README.md) to retrieve the current time. This will give us up-to-date information on the current time and date which we can then use to set the RTC time/date. 

A free API that lets us gather time and date information is the [WorldTime.org](https://worldtimeapi.org/) API. For a full example sketch of how to use this API to set the time on the M5Stick's RTC, [click here](M5_RTC_API/M5_RTC_API.ino).