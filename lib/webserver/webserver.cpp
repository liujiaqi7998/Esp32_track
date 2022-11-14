#include "webserver.h"
#include <Preferences.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
#include <WiFi.h>

AsyncWebServer server(80);
AsyncWebSocket ws("/ws"); // WebSocket对象，url为/

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
    // Handle WebSocket event
    // if (type == WS_EVT_CONNECT)
    // {
    //     // client connected
    //     client->printf("Hello Client %u :)", client->id());
    //     client->ping();
    // }
    
}


void trank_Task(void *parameter)
{
    Serial.println("[线程管理]:启动线程");
    
    while (1)
    {
        ws.printfAll("123");
    }
    
}


void int_web()
{
    
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/html", main_HTML); });
              
    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
    AsyncElegantOTA.begin(&server); // Start AsyncElegantOTA
                                    
    ws.onEvent(onEvent);
    
    server.addHandler(&ws);// attach AsyncWebSocket
    server.begin();

    xTaskCreate(
            trank_Task,   /* Task function. */
            "trank_Task", /* String with name of task. */
            10000,                 /* Stack size in bytes. */
            NULL,                  /* Parameter passed as input of the task */
            1,                     /* Priority of the task. */
            NULL);                 /* Task handle. */
}