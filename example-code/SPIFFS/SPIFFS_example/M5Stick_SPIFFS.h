//========================================================
// File:    M5Stick_SPIFFS
//
// Author:  J. Hathway 2023
//
// Description:
//          Some functions for using SPIFFS to write to 
//          internal SD:
//              - formatSpiffs()
//              - initSPIFFS()
//              - addSPIFFS()
//              - writeSPIFFS()
//              - appendSPIFFS()
//              - readSPIFFS()
//              - removeSPIFFS()
//========================================================
#include <SPIFFS.h>

//========================================================

/// Format SPIFFS - delete all files on SD
void formatSPIFFS()
{
    M5.Lcd.print("Formatting SPIFFS...");
    SPIFFS.format();
    M5.Lcd.println("SPIFFS format completed");
}

//========================================================

/// Initialise SPIFFS - call SPIFFS.begin()
/// @return true on success, false on failure
bool initSPIFFS()
{
    if (!SPIFFS.begin())
    {
        M5.Lcd.print("ERROR: SPIFFS Failed to Start");
        return false;
    }

    M5.Lcd.println("SPIFFS Started");
    return true;
}

//========================================================

/// Add SPIFFS - create an empty file on SD
/// @param filepath (const String&) name of new file
/// @return true on success, false on failure
bool addSPIFFS(const String &filepath)
{
    // Check if file exists
    if (SPIFFS.exists(filepath))
    {
        M5.Lcd.print("ERROR: ");
        M5.Lcd.println(filepath + ": File Already Exists");
        return false;
    }

    File file = SPIFFS.open(filepath, "w");

    // Check if file opened correctly
    if (!file)
    {
        M5.Lcd.print("ERROR: ");
        M5.Lcd.println(filepath + ": Failed to Create File");
        return false;
    }

    M5.Lcd.print(filepath);
    M5.Lcd.println(": New File Created");
    file.close();
    return true;
}

//========================================================

/// Write SPIFFS - overwrite file data
/// @param filepath (const String&) name of file
/// @param data (const String&) data to write to file
/// @return true on success, false on failure
bool writeSPIFFS(const String &filepath, const String &data)
{
    // Check if file exists
    if (!SPIFFS.exists(filepath))
    {
        M5.Lcd.print("ERROR: ");
        M5.Lcd.println(filepath + ": File Not Found");
        return false;
    }

    File file = SPIFFS.open(filepath, "w");

    // Check if file opened correctly
    if (!file)
    {
        M5.Lcd.print("ERROR: ");
        M5.Lcd.println(filepath + ": Failed to Open File");
        return false;
    }

    file.print(data);
    file.close();
    return true;
}

//========================================================

/// Append SPIFFS - append data to file
/// @param filepath (const String&) name of file
/// @param data (const String&) data to append to file
/// @return true on success, false on failure
bool appendSPIFFS(const String &filepath, const String &data)
{
    // Check if file exists
    if (!SPIFFS.exists(filepath))
    {
        M5.Lcd.print("ERROR: ");
        M5.Lcd.println(filepath + ": File Not Found");
        return false;
    }

    File file = SPIFFS.open(filepath, "a");

    // Check if file opened correctly
    if (!file)
    {
        M5.Lcd.print("ERROR: ");
        M5.Lcd.println(filepath + ": Failed to Open File");
        return false;
    }

    file.print(data);
    file.close();
    return true;
}

//========================================================

/// Read SPIFFS - read data from file
/// @param filepath (const String&) name of file
/// @return data (String) file contents
String readSPIFFS(const String &filepath)
{
    // Check if file exists
    if (!SPIFFS.exists(filepath))
    {
        M5.Lcd.print("ERROR: ");
        M5.Lcd.println(filepath + ": File Not Found");
        return "";
    }

    File file = SPIFFS.open(filepath, "r");

    // Check if file opened correctly
    if (!file)
    {
        M5.Lcd.print("ERROR: ");
        M5.Lcd.println(filepath + ": Failed to Open File");
        return "";
    }

    // Read contents to data 
    String data = "";
    for (int i = 0; i < file.size(); i++)
        data += (char)file.read();

    file.close();
    return data;
}

//========================================================

/// Remove SPIFFS - remove a file from SD
/// @param filepath (const String&) name of new file
/// @return true on success, false on failure
bool removeSPIFFS(const String &filepath)
{   
    // Check if file exists
    if (!SPIFFS.exists(filepath))
    {
        M5.Lcd.print("ERROR: ");
        M5.Lcd.println(filepath + ": File Not Found");
        return false;
    }

    SPIFFS.remove(filepath);
    return true;
}
