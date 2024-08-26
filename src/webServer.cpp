#include <LittleFS.h>
#include <AsyncJson.h>
#include "webServer.h"

WebServer::WebServer(uint16_t port) : _server(port) { headers(); }
WebServer::~WebServer() { _server.end(); }

void WebServer::begin() {
    routes();
    _server.begin(); 
}

void WebServer::headers() {
    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "*");
    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE");
}

void WebServer::routes() {
    _server.onNotFound([](AsyncWebServerRequest *request) {
        if (request->method() == HTTP_OPTIONS) return request->send(200);
        request->send(404, "text/plain", "Not Found");
    });

    _server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        AsyncWebServerResponse* response = request->beginResponse(LittleFS, "/index.html.gz", "text/html");
        response->addHeader("Content-Encoding", "gzip");
        request->send(response);
    });
    _server.on("/static/favicon.ico", HTTP_GET, [](AsyncWebServerRequest *request) {
        AsyncWebServerResponse* response = request->beginResponse(LittleFS, "/static/favicon.ico.gz", "image/x-icon");
        response->addHeader("Content-Encoding", "gzip");
        request->send(response);
    });
    _server.on("/static/style.css", HTTP_GET, [](AsyncWebServerRequest *request) {
        AsyncWebServerResponse* response = request->beginResponse(LittleFS, "/static/style.css.gz", "text/css");
        response->addHeader("Content-Encoding", "gzip");
        request->send(response);
    });

    _server.addHandler(new AsyncCallbackJsonWebHandler("/api/json", HTTP_POST, [](AsyncWebServerRequest *request, JsonVariant &json) {
        JsonDocument data;
        if (json.is<JsonArray>()) data = json.as<JsonArray>();
        else if (json.is<JsonObject>()) data = json.as<JsonObject>();
        String response;
        serializeJson(data, response);
        request->send(200, "application/json", response);
        Serial.println(response);
    }));
}
 