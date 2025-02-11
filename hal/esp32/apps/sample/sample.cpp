

#include <lvgl.h>
#include "ui/ui.h"

#include "../app_hal.h"
#include "../../core/app_manager.h"

LV_IMAGE_DECLARE(image_lumia);

/* app info */
static app_info_t hello_info = {
    .code = 0x0000,
    .name = "Sample App",
    .icon = &image_lumia}; /* App icon recommeded size 32x32 */

/* Start tile info */
static start_tile_t hello_tile = {
    .app = hello_info,
    .wide = false,
    .live = NULL,
    .dir = CM_LIVE_NONE};

static lv_obj_t *hello_app_screen; /* Main screen object */


static void hello_launch_event(lv_event_t *e);
static void hello_page_events(lv_event_t *e);
static void hello_app_screen_init(void);
void register_hello_app();


static void hello_launch_event(lv_event_t *e)
{
    if (!hello_app_screen)
    {
        /* Initialize screen */
        hello_app_screen_init();
    }

    lv_screen_load_anim(hello_app_screen, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, false);
}

static void hello_page_events(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_SCREEN_LOADED)
    {
        set_parent(hello_app_screen); /* Set the main components to current screen (Navigation bar, status bar etc)*/
        // Other startup actions goes here

    }
    if (event_code == LV_EVENT_SCREEN_UNLOADED)
    {
        // Other cleanup actions goes here


        set_back_handler(NULL); /* Release the back button handler if set prevously */
        /* Delete the screen */
        lv_obj_delete(hello_app_screen);
        hello_app_screen = NULL;
    }
}

static void hello_app_screen_init(void)
{
    hello_app_screen = lv_obj_create(NULL);
    lv_obj_remove_flag(hello_app_screen, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(hello_app_screen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(hello_app_screen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(hello_app_screen, hello_page_events, LV_EVENT_ALL, NULL);

    /* Add the app top header title if needed */
    cm_create_app_title(hello_app_screen, hello_info.name, hello_info.icon);

    /* Add content as needed */
    lv_obj_t * label = lv_label_create(hello_app_screen);
    lv_obj_set_align(label, LV_ALIGN_CENTER);
    lv_label_set_text(label, "Hello world");

}


/**
 * This function will be called by the app manager. Here we register/add the app icons in the start and app list
 */
void register_hello_app()
{
    /* Add app to the app list and set launch callback */
    cm_app_list(hello_info, hello_launch_event, register_panel);

    /* Add app tile to the start menu and set launch callback */
    cm_start_tile(hello_tile, NULL, hello_launch_event, register_start);

}

/* Needed for app manager to automatically register the app */
struct HelloAppRegister
{
    HelloAppRegister()
    {
        AppManager::registerApp(register_hello_app); /* Set the function that will be called to register the app */
    }
};

static HelloAppRegister hello_app;