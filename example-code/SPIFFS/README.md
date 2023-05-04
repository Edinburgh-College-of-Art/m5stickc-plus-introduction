# Using SPIFFS with M5StickC-Plus

- [Using SPIFFS with M5StickC-Plus](#using-spiffs-with-m5stickc-plus)
	- [Introduction](#introduction)
    - [M5Stick_SPIFFS.h](#m5stick_spiffsh)
        - [formatSPIFFS()](#formatspiffs)
        - [initSPIFFS()](#initspiffs)
        - [addSPIFFS()](#addspiffs)
        - [writeSPIFFS()](#writespiffs)
        - [appendSPIFFS()](#appendspiffs)
        - [readSPIFFS()](#readspiffs)
        - [removeSPIFFS()](#removespiffs)

## Introduction
SPI Flash File Storage (or [SPIFFS](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/storage/spiffs.html)) is a file system for saving files to the internal SD onboard the ESP32 chip inside the M5StickC-Plus board. This allows us to easily store and read from files on the M5Stick, even if the board is turned off and on again. Uses for this might include storing configuration data or preferences for each time we startup the board.

SPIFFS does not support directories, it produces a flat structure. If SPIFFS is mounted under <code>/spiffs</code>, then creating a file with the path <code>/spiffs/tmp/myfile.txt</code> will create a file called <code>/tmp/myfile.txt</code> in SPIFFS, instead of myfile.txt in the directory <code>/spiffs/tmp</code>.

## M5Stick_SPIFFS.h
The <code>M5Stick_SPIFFS.h</code> file contains a number of functions that can quickly access the SPIFFS system for reading, writing and formatting. These functions include:

### formatSPIFFS()
- Returns: void

Calling this function will format the internal SD, clearing any written memory that currently exists. 

**NOTE**: once formatted, you cannot retrieve any deleted files. Only call this funciton if you are sure you want to clear the existing memory.

### initSPIFFS()
- Returns: bool

Calling this function will initialize the SPIFFS system, ready for reading and writing. Function will return true if successful and return false if unsuccessful.

### addSPIFFS()
- Parameters: const String &filepath
- Returns: bool

Calling this function creates an empty file. Function will return true if successful and return false if unsuccessful.

Example usage: <code>addSPIFFS("/m5stick/text.txt");</code>

### writeSPIFFS()
- Parameters: const String &filepath, const String &data
- Returns: bool

Calling this function overwrite data to a pre-existing file. The writeSPIFFS() function will overwrite any data that already exists in the specified file. Function will return true if successful and return false if unsuccessful.

Example usage: <code>addSPIFFS("/m5stick/text.txt", "Hello World");</code>

**NOTE**: once called, you cannot retrieve any over-written data. Only call this funciton if you are sure you want to over-write the existing memory.

### appendSPIFFS()
- Parameters: const String &filepath, const String &data
- Returns: bool

Calling this function append data to a pre-existing file. The appendSPIFFS() function will write the specified data to the end of the specified file. Function will return true if successful and return false if unsuccessful.

Example usage: <code>addSPIFFS("/m5stick/text.txt", "Hello World 2");</code>

### readSPIFFS()
- Parameters: const String &filepath
- Returns: String

Calling this function will return all data written to the specified file. 

Example usage: <code>String msg = readSPIFFS("/m5stick/text.txt");</code>

### removeSPIFFS()
- Parameters: const String &filepath
- Returns: bool

Calling this function will delete a file from SPIFFS. Function will return true if successful and return false

Example usage: <code>removeSPIFFS("/m5stick/text.txt");</code>

