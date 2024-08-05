#include <Arduino.h>
#include <lvgl.h>
#include "PanelLan.h"
// #include <ChronosESP32.h>
#include <Timber.h>
#include "app_hal.h"

#include "ui/ui.h"

#ifdef PLUS
#define SCR 30
#define BOARD BOARD_SC01_PLUS
#define NAME "WT32 SC01 Plus"
#else
#define SCR 8
#define BOARD BOARD_SC01
#define NAME "WT32 SC01"
#endif

PanelLan tft(BOARD);
// ChronosESP32 watch(NAME);

static const uint32_t screenWidth = 320;
static const uint32_t screenHeight = 480;

static lv_disp_draw_buf_t draw_buf;
static lv_disp_drv_t disp_drv;

static lv_color_t disp_draw_buf[2][screenWidth * SCR];

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

void logCallback(Level level, unsigned long time, String message)
{
    Serial.print(message);
}

void hal_setup()
{
    Serial.begin(115200);

    Timber.setLogCallback(logCallback);

    tft.init();
    tft.initDMA();
    tft.startWrite();

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

    ui_init();


    Timber.i("Setup done");
}

void hal_loop()
{
    lv_timer_handler(); /* let the GUI do its work */
    delay(5);
}
