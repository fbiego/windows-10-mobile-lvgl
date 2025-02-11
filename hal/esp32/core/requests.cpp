

#include "requests.h"

Request request[MAX_REQUEST];
HTTPClient http;

bool activeRequest;




void sendSingleRequest(void *parameter)
{
    Timber.v("Start single request task on core %d", xPortGetCoreID());
    RequestTask *task = (RequestTask *)parameter;
    Request *request = task->request;
    RequestCallback callback = task->callback;

    Serial.println(request->url);
    long t = millis();

    if (!WiFi.isConnected()) {
        if (callback)
        {
            callback(request->code, -50, "WiFi not connected", millis() - t);
        }
        delete task; // Free allocated memory
        vTaskDelete(NULL);
    }

    HTTPClient http;
    http.begin(request->url);

    int httpCode;
    if (request->method)
    {
        httpCode = http.POST(request->data);
    }
    else
    {
        httpCode = http.GET();
    }

    String payload = http.getString();
    t = millis() - t;
    request->active = false;

    // Call the provided callback with the request result
    if (callback)
    {
        callback(request->code, httpCode, payload, t);
    }

    http.end();
 
    delete task; // Free allocated memory
    vTaskDelete(NULL);

}

void startSingleRequest(Request *request, RequestCallback callback)
{
    RequestTask *task = new RequestTask{request, callback};
    xTaskCreatePinnedToCore(sendSingleRequest, "SingleRequest", 8192, task, 1, NULL, 0);
}

void requestResult(int requestCode, int statusCode, String payload, long time)
{

    Serial.printf("Request %d received, time %dms, code: %d\n", requestCode, time, statusCode);

    if (statusCode == HTTP_CODE_OK)
    {
        Serial.println(payload);
    }

    switch (requestCode)
    {
    case TIME_REQUEST:
        if (statusCode == HTTP_CODE_OK)
        {
            JsonDocument json;
            deserializeJson(json, payload);
            long t = json["timestamp"].as<long>();
            rtc.setTime(t);
            time_set = true;
        }
        break;
    }
}

void sendRequest(void *parameter)
{
    Timber.v("Start sendRequest task on core %d", xPortGetCoreID());
    long t;

    for (int r = 0; r < MAX_REQUEST; r++)
    {
        if (request[r].active)
        {
            t = millis();
            http.begin(request[r].url);
            int httpCode;
            if (request[r].method)
            {
                httpCode = http.POST(request[r].data);
            }
            else
            {
                httpCode = http.GET();
            }

            String payload = http.getString();

            // http.end();
            t = millis() - t;
            requestResult(request[r].code, httpCode, payload, t);
            request[r].active = false;
        }
    }
    http.end();
    activeRequest = false;
    // When you're done, call vTaskDelete. Don't forget this!
    vTaskDelete(NULL);

    Timber.v("End sendRequest task on core %d", xPortGetCoreID());
}

bool runRequest()
{
    // returns true if the task was created
    // returns false if the previous task has not completed, new one cannot be created
    if (!activeRequest)
    {
        activeRequest = true;
        // xTaskCreatePinnedToCore(
        xTaskCreate(
            sendRequest,     // Function that should be called
            "HTTP Requests", // Name of the task (for debugging)
            8192,            // Stack size (bytes)
            NULL,            // Parameter to pass
            1,               // Task priority
            NULL
            // NULL,               // Task handle
            // 1
        );

        return true;
    }
    else
    {
        return false;
    }
}

