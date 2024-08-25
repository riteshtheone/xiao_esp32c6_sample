#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);
const char *ssid = "realme8266", *pass = "0123456789";

void setup() {
    Serial.begin(115200);
    pinMode(15, OUTPUT);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.printf("WiFi Failed!\n");
        return;
    }
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/plain", "Hello, world");
    });
    server.onNotFound([](AsyncWebServerRequest *request){
        request->send(404, "text/plain", "Not found");
    });
    server.begin();
}

void loop() {
    digitalWrite(15, !digitalRead(15));
    delay(1000);
}