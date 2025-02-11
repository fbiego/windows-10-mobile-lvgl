#include <unistd.h>
#include <ctime>
#include <cstring>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#define SDL_MAIN_HANDLED /*To fix SDL's "undefined reference to WinMain" issue*/
#include SDL_INCLUDE_PATH
#include "drivers/sdl/lv_sdl_mouse.h"
#include "drivers/sdl/lv_sdl_mousewheel.h"
#include "drivers/sdl/lv_sdl_keyboard.h"
#include "app_hal.h"

#include <lvgl.h>

#include "ui/ui.h"
#include "prefs.h"


static const uint32_t screenWidth = SDL_HOR_RES;
static const uint32_t screenHeight = SDL_VER_RES;

const char *daysWk[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
const char *months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};



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
#ifdef OS_WINDOWS
        if (mkdir(folder_name) != 0) {
#else
        if (mkdir(folder_name, 0755) != 0) {
#endif
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

void onWifiStateChange(int state)
{
    savePrefInt("wifi_state", state);
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

    lv_sdl_window_create(SDL_HOR_RES, SDL_VER_RES);
    lv_sdl_mouse_create();
    // lv_sdl_mousewheel_create();
    // lv_sdl_keyboard_create();

    ui_init();

}

void hal_loop(void)
{
    Uint32 lastTick = SDL_GetTicks();
    while(1) {
        SDL_Delay(5);
        Uint32 current = SDL_GetTicks();
        lv_tick_inc(current - lastTick); // Update the tick timer. Tick is new for LVGL 9
        lastTick = current;
        lv_timer_handler(); // Update the UI-


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



