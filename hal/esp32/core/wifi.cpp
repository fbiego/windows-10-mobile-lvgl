

#include "Arduino.h"

#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#include "ui/ui.h"
#include "app_hal.h"

#include "FS.h"
#include "FFat.h"

#define FLASH FFat

WiFiMulti wifiMulti;

wifi_info_t wifis[10];

JsonDocument configs;
bool autoConnect = false;

void scanWifi(void *parameter)
{
    LVGL_MUTEX_LOCK()
    lv_label_set_text(wifi_status, "Searching networks");
    lv_obj_add_flag(refresh_button, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clean(ui_wifiList);
    LVGL_MUTEX_UNLOCK()

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
    int n = WiFi.scanNetworks();

    LVGL_MUTEX_LOCK()
    if (n == 0)
    {
        lv_label_set_text(wifi_status, "no networks found");
    }
    else
    {
        lv_label_set_text_fmt(wifi_status, "Found %d networks", n);
        for (int i = 0; i < n; i++)
        {
            // Print SSID and RSSI for each network found
            if (i >= 10)
            {
                break;
            }
            strncpy(wifis[i].name, WiFi.SSID(i).c_str(), sizeof(wifis[i].name) - 1);
            wifis[i].name[sizeof(wifis[i].name) - 1] = '\0';
            wifis[i].rssi = WiFi.RSSI(i);
            wifis[i].secure = WiFi.encryptionType(i) != WIFI_AUTH_OPEN;
            add_wifi_list(ui_wifiList, wifis[i]);
        }
    }
    lv_obj_remove_flag(refresh_button, LV_OBJ_FLAG_HIDDEN);
    LVGL_MUTEX_UNLOCK()

    vTaskDelete(NULL);
}

void onRefreshWifi()
{

    xTaskCreate(
        scanWifi,    // Function that should be called
        "Scan Wifi", // Name of the task (for debugging)
        4096,        // Stack size (bytes)
        NULL,        // Parameter to pass
        1,           // Task priority
        NULL);
}

void onOpenNetworks()
{
    // LVGL_MUTEX_LOCK()
    if (WiFi.isConnected())
    {
        String wifi = "Connected to " + WiFi.SSID();
        lv_label_set_text(wifi_status, wifi.c_str());
    }
    else
    {
        lv_label_set_text(wifi_status, "Not connected, searching");
        onRefreshWifi();
    }
    // LVGL_MUTEX_UNLOCK()
}

void connectWiFi(void *parameter)
{
    uint8_t status;
    LVGL_MUTEX_LOCK()
    lv_label_set_text(wifi_status, "Connecting");
    lv_obj_add_flag(refresh_button, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clean(ui_wifiList);
    LVGL_MUTEX_UNLOCK()
    while (true)
    {
        status = wifiMulti.run();
        Serial.printf("WiFi trying: %d\n", status);
        if (status == WL_CONNECTED || status == WL_CONNECT_FAILED || status == WL_DISCONNECTED || status == WL_NO_SSID_AVAIL)
        {
            break;
        }
    }
    
    Serial.printf("WiFi exit: %d\n", status);
    String info;
    switch (status)
    {
    case WL_CONNECTED:
        info = "Connected to " + WiFi.SSID();
        break;
    case WL_CONNECT_FAILED:
        info = "Connect failed";
        break;
    case WL_NO_SSID_AVAIL:
        info = "SSID not available";
        break;
    case WL_DISCONNECTED:
        info = "Disconnected";
        break;
    default:
        info = "Error " + String(status);
    }
    LVGL_MUTEX_LOCK()
    lv_label_set_text(wifi_status, info.c_str());
    lv_obj_remove_flag(refresh_button, LV_OBJ_FLAG_HIDDEN);

    if (status == WL_CONNECTED)
    {
        lv_obj_remove_flag(ui_statusPanelWifi, LV_OBJ_FLAG_HIDDEN);
    }
    else
    {
        lv_obj_add_flag(ui_statusPanelWifi, LV_OBJ_FLAG_HIDDEN);
    }
    LVGL_MUTEX_UNLOCK()

    if (status == WL_CONNECTED)
    {
        request[0].active = true;

        if (!autoConnect){
            saveWifiConfigs();
        }
        

        runRequest();
    }
    // When you're done, call vTaskDelete. Don't forget this!
    vTaskDelete(NULL);
}

void onConnectWifi()
{
    // LVGL_MUTEX_LOCK()
    wifiMulti.addAP(lv_label_get_text(wifi_dialog_text), lv_textarea_get_text(wifi_dialog_textarea));
    // LVGL_MUTEX_UNLOCK()
    String name = String(lv_label_get_text(wifi_dialog_text));
    String pass = String(lv_textarea_get_text(wifi_dialog_textarea));
    configs[name] = pass;

    autoConnect = false;

    xTaskCreate(
        connectWiFi,    // Function that should be called
        "WIFI Connect", // Name of the task (for debugging)
        4096,           // Stack size (bytes)
        NULL,           // Parameter to pass
        1,              // Task priority
        NULL);
}

void loadWifiConfigs(bool connect)
{
    String result;

    // Timber.v("Read Task created");

    // Open the file in read mode
    File file = FLASH.open("/wifi.json", FILE_READ);

    if (file)
    {
        // Read data from the file and store it in the result variable
        while (file.available())
        {
            result += (char)file.read();
        }
        file.close();

        // Debug print the result

        deserializeJson(configs, result);
        Serial.println(result);

        if (connect)
        {
            int k = 0;
            for (JsonPair kv : configs.as<JsonObject>())
            {
                wifiMulti.addAP(kv.key().c_str(), kv.value().as<const char *>());
                k++;
            }

            if (k)
            {
                autoConnect = true;
                WiFi.mode(WIFI_STA);
                WiFi.disconnect();
                delay(10);

                xTaskCreate(
                    connectWiFi,    // Function that should be called
                    "WIFI Connect", // Name of the task (for debugging)
                    4096,           // Stack size (bytes)
                    NULL,           // Parameter to pass
                    1,              // Task priority
                    NULL);
            }
        }
    } else {
        Serial.println("Unable to open file");
    }

    
}

void addWifiConfig(String name, String pass)
{
    configs[name] = pass;
}

void saveWifiConfigs()
{
    String data;
    serializeJson(configs, data);
    File file = FLASH.open("/wifi.json", FILE_WRITE);

    Serial.print("Saving wifi data: ");
    Serial.println(data);

    if (file)
    {
        // Write data to the file
        int s = file.print(data);
        file.flush();
        file.close();

        Serial.println("Saved");
    } else {
        Serial.println("Error saving");
    }
}
