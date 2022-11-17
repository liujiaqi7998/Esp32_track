#include "webserver.h"
#include <Preferences.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
#include <WiFi.h>
#include <Adafruit_ICM20X.h>
#include <Adafruit_ICM20948.h>
#include <Adafruit_Sensor.h>

Adafruit_ICM20948 icm;
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
    Serial.println("[线程管理]:启动trank线程");
    if (!icm.begin_I2C(0x68))
    {
        Serial.println("Failed to find ICM20948 chip");
        while (1)
        {
            delay(10);
        }
    }
    while (1)
    {
        sensors_event_t accel;
        sensors_event_t gyro;
        sensors_event_t mag;
        sensors_event_t temp;
        icm.getEvent(&accel, &gyro, &temp, &mag);

        String sd = " { \"t\": [";
        sd = sd + gyro.gyro.x + ", ";
        sd = sd + gyro.gyro.y + ", ";
        sd = sd + gyro.gyro.z + "], \"l\": [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], \"r\": [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0] }";

        ws.printfAll(sd.c_str());

        delay(100);
    }
}

void int_web()
{

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/html", main_HTML); });

    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
    AsyncElegantOTA.begin(&server); // Start AsyncElegantOTA

    ws.onEvent(onEvent);

    server.addHandler(&ws); // attach AsyncWebSocket
    server.begin();

    xTaskCreate(
        trank_Task,   /* Task function. */
        "trank_Task", /* String with name of task. */
        10000,        /* Stack size in bytes. */
        NULL,         /* Parameter passed as input of the task */
        1,            /* Priority of the task. */
        NULL);        /* Task handle. */
}