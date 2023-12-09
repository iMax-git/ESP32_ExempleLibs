# ESP32_ExempleLibs

## Description

This is a collection of examples for the ESP32 microcontroller. The examples are based on the Arduino framework.

## Libs used
- WiFi
- WiFiClient (AP, CL)
- WiFiClientSecure
- WebServer
- ESPAsyncWebServer
- HTTPClient
- ArduinoJson
- ESP32Servo (WIP)
- PubSubClient (MQTT)
- LittleFS

## Fnc used
- debounce (Thanks to esp32io.com)
- deep sleep
- light sleep
- Bargraph class


- void RGB(int rouge, int vert , int bleu);
- void blink_rgb(int rouge, int vert, int bleu, int duree);
- float convert_F_to_C(float fahrenheit);
- byte getInternalTemp()
- String requestToApi(HTTPClient http, WiFiClientSecure client, String url); // requête GET
- String requestToApi(HTTPClient http, WiFiClientSecure client, String url, String payload); // requête POST
- String convertFloatToString(float value);
- String convertIntToString(int value)

