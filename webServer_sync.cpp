/**
 * Unasynchrone Webserver
 * lib_deps =
 *  ESP32WebServer
 * 
*/

#include <Arduino.h>
#include <WiFi.h>
#include <ESP32WebServer.h>
#include <HTTPClient.h>


#define SSID "iPhone de iMax"
#define PASSWORD "iMaxLaPince"

#define REPONSE_CODE_OK 200
#define REPONSE_CODE_NOT_FOUND 404
#define REPONSE_CODE_SERVER_ERROR 500



ESP32WebServer server(80);



void setup() 
{
    
    server.on("/", [](){
          server.send(200, "text/html", "<h1>Hello World!</h1>");
    });

    server.on("/readValue", [](){
        

        server.send(200, "text/plain", "OK");
    });
    server.begin();
}

void loop() 
{
    server.handleClient();
    delay(1);
}