#include <network_config.h>
#include <WiFi.h>
#include <Preferences.h>

char lock_but = 0;
wl_status_t last_network_state = WL_IDLE_STATUS;

void setup_wifi()
{
    Preferences prefs;     // 声明Preferences对象
    prefs.begin("config"); // 打开命名空间config
    WiFi.mode(WIFI_AP_STA);
    String wifi_ssid = prefs.getString("ssid", "");     // 读取ssid
    String wifi_passwd = prefs.getString("passwd", ""); // 读取passwd
    if (wifi_ssid != "" && wifi_passwd != "")
    {
        WiFi.begin(wifi_ssid.c_str(), wifi_passwd.c_str());
        // 点亮LED
        digitalWrite(2, HIGH);
        Serial.println("[网络管理]:WIFI连接到:" + wifi_ssid);
    }
    else
    {
        // 熄灭LED
        digitalWrite(2, LOW);
        Serial.println("[网络管理]:没有读取到WIFI数据，不启动网络");
    }
    prefs.end(); // 关闭命名空间config
}

void network_config_Task(void *parameter)
{
    Serial.println("[线程管理]:启动SmartConfig配网线程");
    Preferences prefs;     // 声明Preferences对象
    prefs.begin("config"); // 打开命名空间config
    WiFi.beginSmartConfig();
    // Wait for SmartConfig packet from mobile
    Serial.println("[网络管理]:等待SmartConfig配网");
    while (!WiFi.smartConfigDone())
    {
        delay(200);
        digitalWrite(2, HIGH);
        delay(200);
        digitalWrite(2, LOW);
    }
    digitalWrite(2, HIGH);
    prefs.putString("ssid", WiFi.SSID());  // 写入ssid
    prefs.putString("passwd", WiFi.psk()); // 写入passwd
    prefs.end();                           // 关闭命名空间config
    Serial.println("[网络管理]:配网完成，重启，等待30秒");
    ESP.restart();
}

void network_config_begin()
{
    if (lock_but == 0)
    {
        lock_but = 1;
        xTaskCreate(
            network_config_Task,   /* Task function. */
            "network_config_Task", /* String with name of task. */
            10000,                 /* Stack size in bytes. */
            NULL,                  /* Parameter passed as input of the task */
            1,                     /* Priority of the task. */
            NULL);                 /* Task handle. */
    }
}