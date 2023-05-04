//==============================================
// File:    M5Stick_ESPNOW.h
//
// Author:  J. Hathway 2023
//
// Dependencies:
//     - M5StickCPlus Library (M5Stack).
//
// Description:
//     - Functions for sending/receiving ESPNOW
//       messages on M5StickCPlus
//===============================================

#ifndef M5STICKC_PLUS
#define M5STICKC_PLUS
#define PRINT(x) M5.Lcd.print(x); Serial.print(x);
#define PRINT_LN(x) M5.Lcd.println(x); Serial.println(x);
#endif

#include <WiFi.h>
#include <esp_now.h>

//==============================================
// PAIR DEVICES
esp_now_peer_info_t _peerInfo;
int _peerCount = 0;

void sendTo(uint8_t *_address)
{
    _peerCount++;

    // register peer
    memcpy(_peerInfo.peer_addr, _address, 6);
    if (esp_now_add_peer(&_peerInfo) != ESP_OK)
    {
        PRINT_LN("Failed to add peer " + String(_peerCount))
        return;
    }
}

//==============================================
// INITIALISE ESPNOW SEND
void espInitSend()
{
    // set device as a Wi-Fi Station
    WiFi.mode(WIFI_STA);

    // init ESPNOW
    if (esp_now_init() != ESP_OK)
    {
        PRINT_LN("Error initializing ESP-NOW")
        return;
    }

    // function called when message is sent
    esp_now_register_send_cb(
        [](const uint8_t *_mac_addr, esp_now_send_status_t _status)
        {
            if (_status != ESP_NOW_SEND_SUCCESS)
                PRINT_LN("Failed to deliver");
        });

    // register peer
    _peerInfo.channel = 0;
    _peerInfo.encrypt = false;
}

//==============================================
// INITIALISE ESPNOW RECEIVE
void espInitRcv()
{
    // Set device as a Wi-Fi Station
    WiFi.mode(WIFI_STA);

    // init ESPNOW
    if (esp_now_init() != ESP_OK)
    {
        PRINT_LN("Error initializing ESP-NOW");
        return;
    }
}

//==============================================
// ESP NOW SEND
template <typename T>
void espSend(T _message)
{
    // send message via ESPNOW
    esp_err_t result = esp_now_send(0, (uint8_t *)&_message, sizeof(_message));

    if (result != ESP_OK)
        PRINT_LN("Error sending the data");
}

//==============================================
// ESPNOW RECEIVE
void *_ptr = nullptr;

template <typename T>
void espReceive(T &_message)
{
    _ptr = &_message;

    // function called when receive is registered
    esp_now_register_recv_cb(
        [](const uint8_t *_mac, const uint8_t *_incomingData, int _len)
        {
            memcpy(_ptr, _incomingData, sizeof(*(T *)_ptr));
        });
}