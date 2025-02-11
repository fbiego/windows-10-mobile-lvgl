#pragma once

#include "Arduino.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Timber.h>
#include <lvgl.h>
#include "../app_hal.h"
#include "MemoryStream.h"

typedef struct ImageUrl
{
    bool active;
    String url;
    int width;
    lv_obj_t *obj;  // LVGL image object
    lv_image_dsc_t dsc;
} ImageUrl;



void startSingleRequest(Request *request, RequestCallback callback);

