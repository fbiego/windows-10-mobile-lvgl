#ifndef APP_HAL_H
#define APP_HAL_H

#include "Arduino.h"
#include <ESP32Time.h>

#ifdef __cplusplus
extern "C" {
#endif




#define MAX_REQUEST 5

#define TIME_REQUEST 0
#define APPS_REQUEST 1
#define BLOG_REQUEST 2
#define BLOG_ITEM_REQUEST 3



typedef struct Request
{
    String url;
    int code;
    bool method;
    String data;
    bool active;
} Request;



typedef void (*RequestCallback)(int requestCode, int statusCode, String payload, long time);

struct RequestTask
{
    Request *request;
    RequestCallback callback;
};

#define LVGL_MUTEX_LOCK()    if (xSemaphoreTake(lvgl_mutex, portMAX_DELAY)) {
#define LVGL_MUTEX_UNLOCK()  xSemaphoreGive(lvgl_mutex); }

extern SemaphoreHandle_t lvgl_mutex; // Global mutex for LVGL
extern ESP32Time rtc;

extern bool time_set;

extern Request request[MAX_REQUEST];

bool runRequest();

void hal_setup(void);
void hal_loop(void);

void startSingleRequest(Request *request, RequestCallback callback);

void saveWifiConfigs();
void loadWifiConfigs(bool connect);

void register_blog_app();


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*APP_HAL_H*/