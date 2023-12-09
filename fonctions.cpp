/*

lib_deps = 
	bblanchon/ArduinoJson@^6.21.3
	madhephaestus/ESP32Servo@^1.1.1
*/


#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h> // EXTERNAL LIBRARY
#include <ESP32Servo.h> // EXTERNAL LIBRARY
#include <PubSubClient.h> // EXTERNAL LIBRARY
#include <WiFiClientSecure.h>



/*
    LED RGB
*/

#define GPIO_LED_ROUGE 25
#define GPIO_LED_VERTE 26
#define GPIO_LED_BLEUE 27

#define GPIO_DAC_0 25
#define GPIO_DAC_1 26

void RGB(int rouge, int vert , int bleu);
void RGB(int rouge, int vert , int bleu)
{
    /*
    Serial.print("Rouge: ");
    Serial.print(rouge);
    Serial.print(" Vert: ");
    Serial.print(vert);
    Serial.print(" Bleu: ");
    Serial.println(bleu);
    */

   int leds[3] = {GPIO_LED_ROUGE, GPIO_LED_VERTE, GPIO_LED_BLEUE};
    int couleurs[3] = {rouge, vert, bleu};
   for (int i = 0; i < 3; i++)
   {
    if (leds[i] == GPIO_DAC_0 || leds[i] == GPIO_DAC_1)
        {
            dacWrite(leds[i], couleurs[i]);
        }
        else
        {
            digitalWrite(leds[i], couleurs[i]);
        }
   }
}

void blink_rgb(int rouge, int vert, int bleu, int duree);
void blink_rgb(int rouge, int vert, int bleu, int duree)
{
    RGB(rouge, vert, bleu);
    delay(duree);
    RGB(0, 0, 0);
    delay(duree);
}


float convert_F_to_C(float fahrenheit);
float convert_F_to_C(float fahrenheit)
{
    return (fahrenheit - 32) / 1.8;
}


/*
Temperature interne
*/

#ifdef __cplusplus
extern "C" {
#endif
    uint8_t temprature_sens_read();
#ifdef __cplusplus
}
#endif

// This fnc need to active WiFi before use
byte getInternalTemp()
{
    byte val;
    while ((val = temprature_sens_read()) == 128) {
        delay(50);
    }
    return(val);
}

/*
    Lecture JSON
*/


DynamicJsonDocument readJson(String payload) {
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, payload);
    return doc;
}


/*
    Requête HTTP
*/


String requestToApi(HTTPClient http, WiFiClientSecure client, String url) { // requête GET
    http.begin(client, url);
    int httpCode = http.GET();
    String payload = http.getString();
    http.end();
    client.stop();
    return payload;
}

String requestToApi(HTTPClient http, WiFiClientSecure client, String url, String payload) { // requête POST
    http.begin(client, url);
    http.addHeader("Content-Type", "application/json");
    int httpCode = http.POST(payload);
    String response = http.getString();
    http.end();
    client.stop();
    return response;
}

/*
    Fonctions de conversion
*/

String convertFloatToString(float value) {
    char buffer[10];
    dtostrf(value, 4, 2, buffer);
    return String(buffer);
}

String convertIntToString(int value) {
    char buffer[10];
    itoa(value, buffer, 10);
    return String(buffer);
}


/****************************/