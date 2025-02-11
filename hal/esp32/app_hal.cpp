
#include "Arduino.h"
#include <lvgl.h>

#ifdef ELECROW
#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#else
#include "PanelLan.h"
#endif
#include <ChronosESP32.h>
#include <ESP32Time.h>
#include <Timber.h>
#include <Preferences.h>
#include "app_hal.h"
#include "core/tone.h"
#include <WiFi.h>

#include "FS.h"
#include "FFat.h"

#include <Adafruit_AMG88xx.h>
#include "core/app_manager.h"

#include "ui/ui.h"

#define FLASH FFat

#ifdef ELECROW
#define SCR 50
#define NAME "ELECROW Terminal"
#elif PLUS
#define SCR 50
#define BOARD BOARD_SC01_PLUS
#define NAME "WT32 SC01 Plus"
#else
#define SCR 8
#define BOARD BOARD_SC01
#define NAME "WT32 SC01"
#endif


#ifdef ELECROW
#include "displays/LGFX_ELECROW_3_5.hpp"
#else
PanelLan tft(BOARD);
#endif

ESP32Time rtc(3600 * 3);
ChronosESP32 watch(NAME);
Preferences prefs;
bool time_set;

Adafruit_AMG88xx amg;

static const uint32_t screenWidth = 320;
static const uint32_t screenHeight = 480;

const unsigned int lvBufferSize = screenWidth * SCR;
uint8_t lvBuffer[2][lvBufferSize];

static lv_display_t *lvDisplay;
static lv_indev_t *lvInput;

SemaphoreHandle_t lvgl_mutex; // Global mutex for LVGL

float pixels[AMG88xx_PIXEL_ARRAY_SIZE];

/* Display flushing */
void my_disp_flush(lv_display_t *display, const lv_area_t *area, unsigned char *data)
{

  uint32_t w = lv_area_get_width(area);
  uint32_t h = lv_area_get_height(area);
  lv_draw_sw_rgb565_swap(data, w * h);

  if (tft.getStartCount() == 0)
  {
    tft.endWrite();
  }
  tft.pushImageDMA(area->x1, area->y1, area->x2 - area->x1 + 1, area->y2 - area->y1 + 1, (uint16_t *)data);
  lv_display_flush_ready(display); /* tell lvgl that flushing is done */
}

/*Read the touchpad*/
void my_touchpad_read(lv_indev_t *indev_driver, lv_indev_data_t *data)
{
  uint16_t touchX, touchY;
  bool touched = tft.getTouch(&touchX, &touchY);
  if (!touched)
  {
    data->state = LV_INDEV_STATE_REL;
  }
  else
  {
    data->state = LV_INDEV_STATE_PR;
    /*Set the coordinates*/
    data->point.x = touchX;
    data->point.y = touchY;
  }
}

/* Tick source, tell LVGL how much time (milliseconds) has passed */
static uint32_t my_tick(void)
{
  return millis();
}

void toneOut(int pitch, int duration)
{ // pitch in Hz, duration in ms
#if defined(BUZZER) && (BUZZER != -1)
    int delayPeriod;
    long cycles, i;

    pinMode(BUZZER, OUTPUT);                     // turn on output pin
    delayPeriod = (500000 / pitch) - 7;             // calc 1/2 period in us -7 for overhead
    cycles = ((long)pitch * (long)duration) / 1000; // calc. number of cycles for loop

    for (i = 0; i <= cycles; i++)
    { // play note for duration ms
        digitalWrite(BUZZER, HIGH);
        delayMicroseconds(delayPeriod);
        digitalWrite(BUZZER, LOW);
        delayMicroseconds(delayPeriod - 1); // - 1 to make up for digitaWrite overhead
    }
    pinMode(BUZZER, INPUT); // shut off pin to avoid noise from other operations
#endif
}

void setPrefBool(const char *key, bool value)
{
    prefs.putBool(key, value);
}
void setPrefInt(const char *key, uint32_t value)
{
    prefs.putULong(key, value);
}

uint32_t getPrefInt(const char *key, uint32_t def)
{
    return prefs.getULong(key, def);
}
bool getPrefBool(const char *key, bool def)
{
    return prefs.getBool(key, def);
}

void onBrightnessChange(int32_t value)
{
    tft.setBrightness(value);
    prefs.putInt("brightness", value);
}
void onTimeoutChange(int16_t selected)
{
}

void onWifiStateChange(int state)
{
    prefs.putInt("wifi_state", state);

}

void logCallback(Level level, unsigned long time, String message)
{
    Serial.print(message);
}

void my_log_cb(const char *buf)
{
  Serial.write(buf, strlen(buf));
}


void listDir(fs::FS &fs, const char *dirname, uint8_t levels)
{
  String listing;
  // Timber.v("Listing directory: %s", dirname);
  listing += "Listing directory: ";
  listing += String(dirname) + "\n";

  File root = fs.open(dirname);
  if (!root)
  {
    listing += "- failed to open directory\n";
  }
  else
  {
    if (!root.isDirectory())
    {
      listing += " - not a directory\n";
    }
    else
    {
      File file = root.openNextFile();
      while (file)
      {
        if (file.isDirectory())
        {
          listing += "  DIR : ";
          listing += String(file.name()) + "\n";
          if (levels)
          {
            listDir(fs, file.name(), levels - 1);
          }
        }
        else
        {
          listing += "  FILE: ";
          listing += file.name();
          listing += "\tSIZE: ";
          listing += String(file.size()) + "\n";
        }
        file = root.openNextFile();
      }
    }
  }

  Serial.println(listing);
}


void hal_setup()
{
    Serial.begin(115200);

    Timber.setLogCallback(logCallback);

    tft.init();
    tft.initDMA();
    tft.startWrite();
    tft.fillScreen(TFT_BLACK);

    toneOut(TONE_EN * 2, 170);
    toneOut(TONE_FS * 2, 170);
    toneOut(TONE_GN * 2, 170);

    prefs.begin("my-app");

    if (!FLASH.begin())
    {
        Serial.println("FFat Mount Failed");
        FLASH.format();

        FLASH.begin();
    }

    // listDir(FLASH, "/", 0);

    lv_init();

    lvgl_mutex = xSemaphoreCreateMutex(); // Create the mutex

    Timber.i("Width %d\tHeight %d", screenWidth, screenHeight);

    /* Set the tick callback */
    lv_tick_set_cb(my_tick);

    /* Create LVGL display and set the flush function */
    lvDisplay = lv_display_create(screenWidth, screenHeight);
    lv_display_set_color_format(lvDisplay, LV_COLOR_FORMAT_RGB565);
    lv_display_set_flush_cb(lvDisplay, my_disp_flush);
    lv_display_set_buffers(lvDisplay, lvBuffer[0], lvBuffer[1], lvBufferSize, LV_DISPLAY_RENDER_MODE_PARTIAL);

    /* Set the touch input function */
    lvInput = lv_indev_create();
    lv_indev_set_type(lvInput, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(lvInput, my_touchpad_read);

    // lv_log_register_print_cb(my_log_cb);

    lv_unlock();

    ui_init();

    // watch.begin();
    tft.setBrightness(prefs.getInt("brightness", 200));

    Timber.i("Setup done");

    loadWifiConfigs(prefs.getInt("wifi_state", 0));

    request[0].method = false;
    request[0].code = TIME_REQUEST;
    request[0].url = "http://iot.fbiego.com/api/v1/time";

    AppManager::initializeApps();  // Automatically calls all registered apps

    load_prefs();
}

void hal_loop()
{

    LVGL_MUTEX_LOCK() 
        lv_timer_handler(); /* let the GUI do its work */
        delay(5);
        lv_label_set_text(ui_statusPanelTime, rtc.getTime("%H:%M").c_str());
        lv_label_set_text(ui_Label41, rtc.getTime("%H:%M").c_str());
        lv_label_set_text(ui_Label39, rtc.getTime("%A, %B %d").c_str());

        if (WiFi.isConnected())
        {
            lv_obj_remove_flag(ui_statusPanelWifi, LV_OBJ_FLAG_HIDDEN);
            if (!time_set && !request[0].active){
                request[0].active = true;
                runRequest();
            }
        }
        else
        {
            lv_obj_add_flag(ui_statusPanelWifi, LV_OBJ_FLAG_HIDDEN);
        }

    LVGL_MUTEX_UNLOCK() 
}
