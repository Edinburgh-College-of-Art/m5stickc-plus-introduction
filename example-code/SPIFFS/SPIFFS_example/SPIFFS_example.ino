#include <M5StickCPlus.h>
#include "M5Stick_SPIFFS.h"

String file_name = "/notes.txt";

void setup()
{
    M5.begin();

    // format SD
    formatSPIFFS();

    // mount SPIFFS
    initSPIFFS();

    // add empty file
    addSPIFFS(file_name);

    // write/overwrite file
    writeSPIFFS(file_name, "Hello World");

    // append data to file
    appendSPIFFS(file_name, "\nAhoy-hoy");

    // read file
    M5.Lcd.println(readSPIFFS(file_name));

    // remove file
    removeSPIFFS(file_name);
}

void loop()
{
}