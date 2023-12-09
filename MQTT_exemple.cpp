#include <Arduino.h>
#include "WiFi.h"
#include "PubSubClient.h"
#include  "Wire.h"
  // WiFi 
const char *ssid = ""; // Entrez votre SSID WiFi  
const char *password = ""; // Entrez votre mot de passe WiFi 
  
// MQTT Broker 
const char *mqtt_broker = ""; 
const char *topic = ""; 
const char *mqtt_username = ""; 
const char *mqtt_password = ""; 
const int mqtt_port = 1883; 
WiFiClient espClient; 
PubSubClient client(espClient); 


void callback(char *topic, byte *payload, unsigned int length);
void setup() { 
    //Mise de la vitesse de transmission à 9600 bauds; 
    Serial.begin(9600); 

    // Connecting to a Wi-Fi network 
    WiFi.begin(ssid, password); 
    while (WiFi.status() != WL_CONNECTED) { 
        delay(500); 
        Serial.println("Connecting to WiFi.."); 
    } 
    Serial.println("Connected to the Wi-Fi network"); 

    //connexion au broker MQTT  
    client.setServer(mqtt_broker, mqtt_port); 
    client.setCallback(callback); 
    while (!client.connected()) { 
        String client_id = "esp32-client-"; 
        client_id += String(WiFi.macAddress()); 
        Serial.printf("The client %s connects to the public MQTT brokern", client_id.c_str()); 
        if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) { 
            Serial.println("Public EMQX MQTT broker connected"); 
        } else { 
            Serial.print("failed with state "); 
            Serial.print(client.state()); 
            delay(2000); 
        } 
    } 
    // Publish et subscribe 
    client.publish(topic, "Hi, I'm ESP32"); 
    client.subscribe(topic);
} 

  // Reception du message MQTT 
void callback(char *topic, byte *payload, unsigned int length) { 
    Serial.print("Message arrived in topic: "); 
    Serial.println(topic); 
    Serial.print("Message:"); 
    for (int i = 0; i < length; i++) { 
        Serial.print((char) payload[i]); 
    } 
    Serial.println(); 
    Serial.println("-----------------------"); 
}

void loop() { 

  client.loop(); 

} 