#include <unistd.h>
#include <ctime>
#include <cstring>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#define SDL_MAIN_HANDLED /*To fix SDL's "undefined reference to WinMain" issue*/
#include SDL_INCLUDE_PATH
#include "display/monitor.h"
#include "indev/mouse.h"
#include "indev/mousewheel.h"
#include "indev/keyboard.h"
#include "sdl/sdl.h"
#include "app_hal.h"

#include <lvgl.h>

#include "ui/ui.h"
#include "prefs.h"


static const uint32_t screenWidth = SDL_HOR_RES;
static const uint32_t screenHeight = SDL_VER_RES;

const char *daysWk[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
const char *months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

/**
 * A task to measure the elapsed time for LittlevGL
 * @param data unused
 * @return never return
 */
static int tick_thread(void *data)
{
    (void)data;

    while (1)
    {
        SDL_Delay(5);   /*Sleep for 5 millisecond*/
        lv_tick_inc(5); /*Tell LittelvGL that 5 milliseconds were elapsed*/
    }

    return 0;
}

/* Mouse read callback for SDL */
void sdl_mouse_read2(lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{
    /*Get the current position and the state of the mouse*/
    int32_t x, y;
    uint32_t state = SDL_GetMouseState(&x, &y);

    /*Set the coordinates and the pressed state*/
    data->point.x = x;
    data->point.y = y;

    /*Button state: 1: pressed, 0: released*/
    data->state = state ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;

    // return false; /*No buffering now so no more data read*/
}

void takeScreenshot(int width, int height) {
    // Create a surface to hold the screenshot
    SDL_Surface *surface = SDL_CreateRGBSurface(0, width, height, 32,
                                                0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
    if (surface == NULL) {
        fprintf(stderr, "Failed to create surface for screenshot: %s\n", SDL_GetError());
        show_alert("Error", "Failed to create surface for screenshot");
        return;
    }

    // Read pixels from the current framebuffer
    if (SDL_RenderReadPixels(SDL_GetRenderer(SDL_GetWindowFromID(1)), NULL, SDL_PIXELFORMAT_ARGB8888, surface->pixels, surface->pitch) != 0) {
        fprintf(stderr, "Failed to read pixels for screenshot: %s\n", SDL_GetError());
        show_alert("Error", "Failed to read pixels for screenshot");
        SDL_FreeSurface(surface);
        return;
    }

    const char* folder_name = "img";

    // Create the folder if it doesn't exist
    struct stat st = {0};
    if (stat(folder_name, &st) == -1) {
        if (mkdir(folder_name) != 0) {
            fprintf(stderr, "Failed to create directory: %s\n", folder_name);
            show_alert("Error", "Failed to create directory");
            SDL_FreeSurface(surface);
            return;
        }
    }

    // Create a filename for the screenshot
    time_t now = time(0);
    tm *ltm = localtime(&now);

    char filename[50];
    snprintf(filename, sizeof(filename), "%s/screenshot-%02d-%02d-%02d.bmp", folder_name, ltm->tm_hour, ltm->tm_min, ltm->tm_sec);

    // Save the surface as a BMP image
    if (SDL_SaveBMP(surface, filename) != 0) {
        fprintf(stderr, "Failed to save screenshot: %s\n", SDL_GetError());
        show_alert("Error", "Failed to save screenshot");
        SDL_FreeSurface(surface);
        return;
    }

    printf("Screenshot saved as %s\n", filename);
    show_alert("Screenshot", "Screenshot saved to img folder");

    // Free the surface
    SDL_FreeSurface(surface);
}


void setPrefBool(const char *key, bool value)
{
    savePrefBool(key, value);
}
void setPrefInt(const char *key, uint32_t value)
{
    savePrefInt(key, value);
}

uint32_t getPrefInt(const char *key, uint32_t def)
{
    uint32_t v;
    if (readPrefInt(key, &v)){
        return v;
    }
    return def;
}
bool getPrefBool(const char *key, bool def)
{
    bool v;
    if (readPrefBool(key, &v)){
        return v;
    }
    return def;

}

void onBrightnessChange(int32_t value) 
{
    savePrefInt("brightness", value);
}
void onTimeoutChange(int16_t selected) 
{
    savePrefInt("timeout", selected);
}

void hal_setup(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return;
    }
// Workaround for sdl2 `-m32` crash
// https://bugs.launchpad.net/ubuntu/+source/libsdl2/+bug/1775067/comments/7
#ifndef WIN32
    setenv("DBUS_FATAL_WARNINGS", "0", 1);
#endif

    lv_init();

    /* Add a display
     * Use the 'monitor' driver which creates window on PC's monitor to simulate a display*/

    static lv_disp_draw_buf_t disp_buf;
    static lv_color_t buf[SDL_HOR_RES * 10];                       /*Declare a buffer for 10 lines*/
    lv_disp_draw_buf_init(&disp_buf, buf, NULL, SDL_HOR_RES * 10); /*Initialize the display buffer*/

    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);           /*Basic initialization*/
    disp_drv.flush_cb = sdl_display_flush; /*Used when `LV_VDB_SIZE != 0` in lv_conf.h (buffered drawing)*/
    disp_drv.draw_buf = &disp_buf;
    disp_drv.hor_res = SDL_HOR_RES;
    disp_drv.ver_res = SDL_VER_RES;
    // disp_drv.disp_fill = monitor_fill;      /*Used when `LV_VDB_SIZE == 0` in lv_conf.h (unbuffered drawing)*/
    // disp_drv.disp_map = monitor_map;        /*Used when `LV_VDB_SIZE == 0` in lv_conf.h (unbuffered drawing)*/
    lv_disp_drv_register(&disp_drv);

    /* Add the mouse as input device
     * Use the 'mouse' driver which reads the PC's mouse*/
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv); /*Basic initialization*/
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = sdl_mouse_read2; /*This function will be called periodically (by the library) to get the mouse position and state*/
    lv_indev_drv_register(&indev_drv);

    sdl_init();

    ui_init();

    /* Tick init.
     * You have to call 'lv_tick_inc()' in periodically to inform LittelvGL about how much time were elapsed
     * Create an SDL thread to do this*/
    SDL_CreateThread(tick_thread, "tick", NULL);
}

void hal_loop(void)
{
    SDL_Event event;

    while (1)
    {
        SDL_Delay(5);
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    // Handle quit event (e.g., user closes the window)
                    // You might want to add code to gracefully exit your program here
                    break;
                case SDL_KEYDOWN:
                    // Handle key press event
                    // SDL_KEYDOWN event occurs when a key is pressed
                    // You can get the pressed key using event.key.keysym.sym
                    switch (event.key.keysym.sym)
                    {
                        // Example for handling specific keys
                        case SDLK_UP:
                            // Handle the up arrow key press
                            break;
                        case SDLK_DOWN:
                            // Handle the down arrow key press
                            break;
                        case SDLK_s:
                            takeScreenshot(SDL_HOR_RES, SDL_VER_RES);
                            break;
                    }
                    break;
                case SDL_KEYUP:
                    // Handle key release event if needed
                    // SDL_KEYUP event occurs when a key is released
                    break;
            }
        }

        lv_task_handler();

        time_t now = time(0);
        tm *ltm = localtime(&now);

        // Extract time fields
        int second = ltm->tm_sec;
        int minute = ltm->tm_min;
        int hour = ltm->tm_hour;
        bool am = hour < 12;
        int day = ltm->tm_mday;
        int month = 1 + ltm->tm_mon;    // Month starts from 0
        int year = 1900 + ltm->tm_year; // Year is since 1900
        int weekday = ltm->tm_wday;


        lv_label_set_text_fmt(ui_statusPanelTime, "%02d:%02d", hour, minute);
        lv_label_set_text_fmt(ui_Label41, "%02d:%02d", hour, minute);
        lv_label_set_text_fmt(ui_Label39, "%s, %s %d", daysWk[weekday % 7], months[(month - 1) % 12], day);

    }
}
