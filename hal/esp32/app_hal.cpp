
#include "Arduino.h"
#include <lvgl.h>

#ifdef ELECROW
#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#else
#include "PanelLan.h"
#endif
#include <ChronosESP32.h>
#include <Timber.h>
#include <Preferences.h>
#include "app_hal.h"

#include <Adafruit_AMG88xx.h>

#include "ui/ui.h"

#ifdef ELECROW
#define SCR 10
#define NAME "ELECROW Terminal"
#elif PLUS
#define SCR 30
#define BOARD BOARD_SC01_PLUS
#define NAME "WT32 SC01 Plus"
#else
#define SCR 8
#define BOARD BOARD_SC01
#define NAME "WT32 SC01"
#endif


#ifdef ELECROW
class LGFX : public lgfx::LGFX_Device
{

    lgfx::Panel_ILI9488 _panel_instance;

    lgfx::Bus_Parallel16 _bus_instance;

    lgfx::Light_PWM _light_instance;

    lgfx::Touch_FT5x06 _touch_instance;

public:
    LGFX(void)
    {
        {
            auto cfg = _bus_instance.config();

            cfg.port = 0;
            cfg.freq_write = 40000000;
            cfg.pin_wr = 18;  // pin number connecting WR
            cfg.pin_rd = 48;  // pin number connecting RD
            cfg.pin_rs = 45;  // Pin number connecting RS(D/C)
            cfg.pin_d0 = 47;  // pin number connecting D0
            cfg.pin_d1 = 21;  // pin number connecting D1
            cfg.pin_d2 = 14;  // pin number connecting D2
            cfg.pin_d3 = 13;  // pin number connecting D3
            cfg.pin_d4 = 12;  // pin number connecting D4
            cfg.pin_d5 = 11;  // pin number connecting D5
            cfg.pin_d6 = 10;  // pin number connecting D6
            cfg.pin_d7 = 9;   // pin number connecting D7
            cfg.pin_d8 = 3;   // pin number connecting D8
            cfg.pin_d9 = 8;   // pin number connecting D9
            cfg.pin_d10 = 16; // pin number connecting D10
            cfg.pin_d11 = 15; // pin number connecting D11
            cfg.pin_d12 = 7;  // pin number connecting D12
            cfg.pin_d13 = 6;  // pin number connecting D13
            cfg.pin_d14 = 5;  // pin number connecting D14
            cfg.pin_d15 = 4;  // pin number connecting D15

            _bus_instance.config(cfg);              // Apply the settings to the bus.
            _panel_instance.setBus(&_bus_instance); // Sets the bus to the panel.
        }

        {                                        // Set display panel control.
            auto cfg = _panel_instance.config(); // Get the structure for display panel settings.

            cfg.pin_cs = -1;   // Pin number to which CS is connected (-1 = disable)
            cfg.pin_rst = -1;  // pin number where RST is connected (-1 = disable)
            cfg.pin_busy = -1; // pin number to which BUSY is connected (-1 = disable)

            // * The following setting values ​​are set to general default values ​​for each panel, and the pin number (-1 = disable) to which BUSY is connected, so please try commenting out any unknown items.

            cfg.memory_width = 320;  // Maximum width supported by driver IC
            cfg.memory_height = 480; // Maximum height supported by driver IC
            cfg.panel_width = 320;   // actual displayable width
            cfg.panel_height = 480;  // actual displayable height
            cfg.offset_x = 0;        // Panel offset in X direction
            cfg.offset_y = 0;        // Panel offset in Y directioncfg.offset_rotation = 2;
            cfg.dummy_read_pixel = 8;
            cfg.dummy_read_bits = 1;
            cfg.readable = false;
            cfg.invert = false;
            cfg.rgb_order = false;
            cfg.dlen_16bit = true;
            cfg.bus_shared = true;

            _panel_instance.config(cfg);
        }
        {                                        // Set backlight control. (delete if not necessary)
            auto cfg = _light_instance.config(); // Get the structure for backlight configuration.

            cfg.pin_bl = 46;     // pin number to which the backlight is connected
            cfg.invert = false;  // true to invert backlight brightness
            cfg.freq = 44100;    // backlight PWM frequency
            cfg.pwm_channel = 0; // PWM channel number to use

            _light_instance.config(cfg);
            _panel_instance.setLight(&_light_instance); // Sets the backlight to the panel.
        }

        { // Configure settings for touch screen control. (delete if not necessary)
          auto cfg = _touch_instance.config();

          cfg.x_min = 0;   // Minimum X value (raw value) obtained from the touchscreen
          cfg.x_max = 319; // Maximum X value (raw value) obtained from the touchscreen
          cfg.y_min = 0;   // Minimum Y value obtained from touchscreen (raw value)
          cfg.y_max = 479; // Maximum Y value (raw value) obtained from the touchscreen
          cfg.pin_int = -1; // pin number to which INT is connected
          cfg.bus_shared = true;
          cfg.offset_rotation = 0;

          // For I2C connection
          cfg.i2c_port = 0;    // Select I2C to use (0 or 1)
          cfg.i2c_addr = 0x38; // I2C device address number
          cfg.pin_sda = 38;     // pin number where SDA is connected
          cfg.pin_scl = 39;     // pin number to which SCL is connected
          cfg.freq = 400000;   // set I2C clock

          _touch_instance.config(cfg);
          _panel_instance.setTouch(&_touch_instance); // Set the touchscreen to the panel.
        }

        setPanel(&_panel_instance); // Sets the panel to use.
    }
};

LGFX tft;
#else
PanelLan tft(BOARD);
#endif
ChronosESP32 watch(NAME);
Preferences prefs;

Adafruit_AMG88xx amg;

static const uint32_t screenWidth = 320;
static const uint32_t screenHeight = 480;

static lv_disp_draw_buf_t draw_buf;
static lv_disp_drv_t disp_drv;

static lv_color_t disp_draw_buf[2][screenWidth * SCR];
float pixels[AMG88xx_PIXEL_ARRAY_SIZE];

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    if (tft.getStartCount() == 0)
    {
        tft.endWrite();
    }
    tft.pushImageDMA(area->x1, area->y1, area->x2 - area->x1 + 1, area->y2 - area->y1 + 1, (lgfx::swap565_t *)&color_p->full);
    lv_disp_flush_ready(disp); /* tell lvgl that flushing is done */
}

/*Read the touchpad*/
void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
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

void logCallback(Level level, unsigned long time, String message)
{
    Serial.print(message);
}

void my_log_cb(const char *buf)
{
  Serial.write(buf, strlen(buf));
}


void hal_setup()
{
    Serial.begin(115200);

    Timber.setLogCallback(logCallback);

    tft.init();
    tft.initDMA();
    tft.startWrite();
    tft.fillScreen(TFT_BLACK);

    prefs.begin("my-app");

    lv_init();

    Timber.i("Width %d\tHeight %d", screenWidth, screenHeight);

    lv_disp_draw_buf_init(&draw_buf, disp_draw_buf[0], disp_draw_buf[1], screenWidth * SCR);

    /* Initialize the display */
    lv_disp_drv_init(&disp_drv);
    /* Change the following line to your display resolution */
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    /* Initialize the input device driver */
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register(&indev_drv);

    lv_log_register_print_cb(my_log_cb);

    ui_init();

    watch.begin();
    tft.setBrightness(prefs.getInt("brightness", 200));

    Timber.i("Setup done");

    thermal_status = amg.begin();
}

void hal_loop()
{
    lv_timer_handler(); /* let the GUI do its work */
    delay(5);

    watch.loop();

    if (thermal_active){
        amg.readPixels(pixels);

        uint32_t c = lv_obj_get_child_cnt(ui_gridTempPanel);
        float total = 0;
        float high = -20;
        float low = 80;

        for (int a = 0; a < c; a++){
            total += pixels[a];

            if (pixels[a] < low){
                low = pixels[a];
            }
            if (pixels[a] > high){
                high = pixels[a];
            }

            lv_color_t color = lv_color_hsv_to_rgb(lv_map(int(pixels[a]), -20, 80, 250, 359), 66, 100); //250, 359, -20, 80
            lv_obj_t *px = lv_obj_get_child(ui_gridTempPanel, a);
            lv_obj_set_style_bg_color(px, color, LV_PART_MAIN | LV_STATE_DEFAULT);

            if (a >= AMG88xx_PIXEL_ARRAY_SIZE){
                break;
            }
        }
        if (total != 0.0){
            lv_label_set_text_fmt(ui_averageTemp, "Average\n%.2f°C", total / AMG88xx_PIXEL_ARRAY_SIZE);
        } else {
            lv_label_set_text(ui_averageTemp, "Average\nNaN");
        }
        lv_label_set_text_fmt(ui_lowTemp, "Low\n%.2f°C", low);
        lv_label_set_text_fmt(ui_highTemp, "High\n%.2f°C", high);
    }

    lv_label_set_text(ui_statusPanelTime, watch.getTime("%H:%M").c_str());
    lv_label_set_text(ui_Label41, watch.getTime("%H:%M").c_str());
    lv_label_set_text(ui_Label39, watch.getTime("%A, %B %d").c_str());
}
