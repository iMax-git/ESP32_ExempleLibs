/*

lib_deps =
	git@github.com:knolleary/pubsubclient.git

*/

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

#define SSID "iPhone de iMax"
#define PASSWORD "iMaxLaPince"

#define MQTT_SERVER ""
#define MQTT_PORT 1883
#define MQTT_USER ""
#define MQTT_PASSWORD ""

WiFiClient espClient;

PubSubClient client(espClient);

void setup() 
{
    Serial.begin(9600);
    delay(1000);

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

    client.setServer(MQTT_SERVER, MQTT_PORT);
    client.setCallback([](char* topic, byte* payload, unsigned int length) {
        Serial.print("Message reçu [");
        Serial.print(topic);
        Serial.print("] ");
        for (int i = 0; i < length; i++) {
            Serial.print((char)payload[i]);
        }
        Serial.println();
    });

    if (!client.connect("ESP32Client", MQTT_USER, MQTT_PASSWORD)) {
        Serial.println("Erreur de connexion au broker MQTT.");
        Serial.flush();
        delay(50);
        exit(-1);
    } else {
        Serial.println("Connexion au broker MQTT établie.");
        Serial.flush();
    }

    client.subscribe("test");
}

void loop() 
{
    client.loop();
    delay(1);
}

void publish(const char* topic, const char* payload);
void publish(const char* topic, const char* payload)
{
    client.publish(topic, payload);
}

void callback(char* topic, byte* payload, unsigned int length);
void callback(char* topic, byte* payload, unsigned int length)
{
    Serial.print("Message reçu [");
    Serial.print(topic);
    Serial.print("] ");
    for (int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
    }
    Serial.println();
}
