#include <Arduino.h>
#include <WiFi.h>
#include <LittleFS.h>
#include "webServer.h"

WebServer webServer(80);
const char *ssid = "realme8266", *pass = "0123456789";

void setup() {
    Serial.begin(115200);
    pinMode(15, OUTPUT);
    if (!LittleFS.begin()) {
        Serial.println("Failed to mount LittleFS");
        delay(2000);
        ESP.restart();
    }
    Serial.println("LittleFS mounted successfully");
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println("WiFi Connection Failed!");
        delay(2000);
        ESP.restart();
    }
    Serial.print("IP Address:- ");
    Serial.println(WiFi.localIP());
    webServer.begin();
}

void loop() {
    digitalWrite(15, !digitalRead(15));
    delay(1000);
}