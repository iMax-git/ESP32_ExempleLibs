#include <Arduino.h>
#include <WiFi.h>


#ifndef WIFI_AP_NAME
#define WIFI_AP_NAME "Diard"
#endif

#ifndef WIFI_AP_PASSWORD
#define WIFI_AP_PASSWORD "iMaxLaPince"
#endif


void setup() {
    
    WiFi.mode(WIFI_AP);
    if (!WiFi.softAP(WIFI_AP_NAME, WIFI_AP_PASSWORD)) {
        Serial.println("Erreur démarrage point d'accès.");
        Serial.flush();
        delay(50);
        exit(-1);
    } else {
        Serial.print("\nPoint d'accès WiFi démarré: ");
        Serial.println(WiFi.softAPSSID());
        Serial.print("address IP: ");
        Serial.println(WiFi.softAPIP());
        Serial.flush();
    }

    // Async server or other stuff

}