#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>


#define SSID "iPhone de iMax"
#define PASSWORD "iMaxLaPince"


WiFiClientSecure client; // Implémenté par HTTPClient



void setup() 
{
    Serial.begin(9600);
    delay(1000);

    client.setInsecure();

    WiFi.begin(SSID, PASSWORD);
    Serial.print("Tentative de connexion à ");
    Serial.println(SSID);
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("Connexion établie!");
    Serial.print("Adresse IP: ");
    Serial.println(WiFi.localIP());

    
}


void loop() 
{
   
}
