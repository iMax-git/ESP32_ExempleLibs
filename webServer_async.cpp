/*
lib_deps =
	https://github.com/me-no-dev/ESPAsyncWebServer.git
	AsyncTCP

*/

#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <HTTPClient.h>



AsyncWebServer server(80);


void setup() 
{

    // Exemple à cumuler avec src/Wifi_AP.cpp
    // ou src/Wifi_CL.cpp


    // server.on("<route>", METHOD(HTTP_GET,HTTP_POST), [](AsyncWebServerRequest *request){
    //     // code
    //    request->send(200, "text/plain", "Hello, world");
    //     request->send(200, "text/html", "<html><body><h1>Hello, world</h1></body></html>");
    //     request->send(200, "application/json", "{\"hello\":\"world\"}");
    //     request->send(200, "text/xml", "<message>Hello, world</message>");
    // });
    
    
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        Serial.println("requête sur /");
        request->send(LittleFS, "/needle/needle_analog.html", "text/html" );
    });
    server.on("/readValue", [](AsyncWebServerRequest *req) {
        String const mesures =
            String{analogRead(A3)}
            + ","
            + String{convert_F_to_C(getInternalTemp())}
            + '\n';
        Serial.printf("requête sur readValue. mesures: %s\n", mesures.c_str());
        req->send(200, "text/plain", mesures.c_str());
    });

    
    server.begin();
}

void loop() 
{
   
}