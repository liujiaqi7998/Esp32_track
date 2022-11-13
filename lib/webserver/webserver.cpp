#include "webserver.h"
#include <Preferences.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
#include <WiFi.h>

AsyncWebServer server(80);

void int_web()
{
    
    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
    AsyncElegantOTA.begin(&server); // Start AsyncElegantOTA
                                    // attach AsyncWebSocket
    server.begin();
}