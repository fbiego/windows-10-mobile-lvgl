

#include <lvgl.h>
#include "../app_hal.h"
#include "ui/ui.h"
#include <ArduinoJson.h>
#include <Timber.h>

#include "../../core/requests.h"
#include "../../core/app_manager.h"

#define MAX_IMAGES 7

static TaskHandle_t image_task_handle = NULL;

static lv_obj_t *fbiego_app_screen;
static lv_obj_t *main_cont;
static lv_obj_t *load_spinner;

LV_IMAGE_DECLARE(image_user);

static Request projects = {
    .url = "http://iot.fbiego.com/api/projects.json",
    .code = 564,
    .method = false,
    .data = "",
    .active = true};

static app_info_t fbiego = {
    .code = 0x0000,
    .name = "fbiego",
    .icon = &image_user};

static start_tile_t fbiego_tile = {
    .app = fbiego,
    .wide = false,
    .live = NULL,
    .dir = CM_LIVE_NONE};

static ImageUrl img_url[MAX_IMAGES];

static void fbiego_app_screen_init(void);
static void fbiego_launch_event(lv_event_t *e);
static lv_obj_t *add_item(const char *title, const char *category, const char *text, const char *date);
static void add_text(const char *text);
static void load_image(uint8_t index);


static void imageRequest(void *parameter)
{
    Timber.v("Start imageRequest task on core %d", xPortGetCoreID());
    for (int i = 0; i < MAX_IMAGES; i++)
    {
        if (img_url[i].active)
        {
            load_image(i);
        }
    }
    Timber.i("Image task complete");
    image_task_handle = NULL;
    vTaskDelete(NULL);
}

static void load_image(uint8_t index)
{

    if (index >= MAX_IMAGES)
    {
        return;
    }
    if (!img_url[index].active)
    {
        return;
    }
    if (img_url[index].obj == NULL)
    {
        Timber.e("Image object null");
        return;
    }

    Timber.i("Load image %d", index);
    long t = millis();

    HTTPClient httpi;

    const char *headerkeys[] = {"X-Image-Width", "X-Image-Height", "X-Image-Data-Size"};
    size_t headerkeyssize = sizeof(headerkeys) / sizeof(char *);

    httpi.begin("http://iot.fbiego.com/lvgl/image");
    httpi.collectHeaders(headerkeys, headerkeyssize);

    int httpCode = httpi.POST("{\"url\": \"" + img_url[index].url + "\", \"width\": " + String(img_url[index].width) + " }");
    if (httpCode == HTTP_CODE_OK)
    {

        int w = httpi.header("X-Image-Width").toInt();
        int h = httpi.header("X-Image-Height").toInt();
        int size = httpi.header("X-Image-Data-Size").toInt();

        Timber.i("Image properties: %dx%d %d bytes", w, h, size);

        if (xSemaphoreTake(lvgl_mutex, portMAX_DELAY))
        {
            // lv_obj_set_height(img_url[index].obj, h);
            lv_obj_set_style_text_color(img_url[index].obj, lv_color_hex(0x33FF2F), LV_PART_MAIN | LV_STATE_DEFAULT);
            xSemaphoreGive(lvgl_mutex);
        }

        auto progressCallback = [&index](float progress, size_t bytesDownloaded, size_t totalBytes)
        {
            // Serial.printf("Progress: %.2f%% (%zu/%zu bytes)\n", progress, bytesDownloaded, totalBytes);

            char buffer[64];
            snprintf(buffer, sizeof(buffer), LV_SYMBOL_DOWNLOAD "  Loading image... %.1f%%", progress);

            if (xSemaphoreTake(lvgl_mutex, portMAX_DELAY))
            {
                lv_image_set_src(img_url[index].obj, buffer);
                xSemaphoreGive(lvgl_mutex);
            }
        };

        Timber.i("Available heap %d, max alloc %d", ESP.getFreeHeap(), ESP.getMaxAllocHeap());
        Timber.i("PSRAM size: %dMB, available %d, max alloc %d", (ESP.getPsramSize() / (1000000)), ESP.getFreePsram(), ESP.getMaxAllocPsram());
        

        img_url[index].dsc.data = (uint8_t *)malloc(size);
        if (img_url[index].dsc.data == NULL)
        {
            Timber.e("Failed to allocate memory for image");
            if (xSemaphoreTake(lvgl_mutex, portMAX_DELAY))
            {
                lv_image_set_src(img_url[index].obj, LV_SYMBOL_WARNING "  Failed to allocate memory");
                lv_obj_set_style_text_color(img_url[index].obj, lv_color_hex(0xFF5F2F), LV_PART_MAIN | LV_STATE_DEFAULT);
                xSemaphoreGive(lvgl_mutex);
            }
        }
        else
        {
            MemoryStream memoryStream((uint8_t *)img_url[index].dsc.data, size, size, progressCallback);

            httpi.writeToStream(&memoryStream);

            // Timber.i("Downloaded %zu bytes to memory", memoryStream.getPosition());

            if (xSemaphoreTake(lvgl_mutex, portMAX_DELAY))
            {
                img_url[index].dsc.header.cf = LV_COLOR_FORMAT_RGB565;
                img_url[index].dsc.header.magic = LV_IMAGE_HEADER_MAGIC;
                img_url[index].dsc.data_size = size;
                img_url[index].dsc.header.w = w;
                img_url[index].dsc.header.h = h;

                lv_image_set_src(img_url[index].obj, &img_url[index].dsc);
                t = millis() - t;
                Timber.i("Shown image: Load time %zums ", t);

                xSemaphoreGive(lvgl_mutex);
            }
        }
    }
    else
    {
        char buffer[64];
        snprintf(buffer, sizeof(buffer), LV_SYMBOL_WARNING "  Failed to loading image.\nHTTP Error %d", httpCode);

        if (xSemaphoreTake(lvgl_mutex, portMAX_DELAY))
        {
            lv_image_set_src(img_url[index].obj, buffer);
            lv_obj_set_style_text_color(img_url[index].obj, lv_color_hex(0xFF5F2F), LV_PART_MAIN | LV_STATE_DEFAULT);
            xSemaphoreGive(lvgl_mutex);
        }
    }
    httpi.end();
}

static void free_images()
{
    for (int i = 0; i < MAX_IMAGES; i++)
    {
        if (img_url[i].dsc.data != NULL)
        {
            Timber.i("Freeing image at index %d Size: %d", i, img_url[i].dsc.data_size);
            free((void *)img_url[i].dsc.data);
            img_url[i].dsc.data = NULL;
        }
        if (img_url[i].obj)
        {
            img_url[i].obj = NULL;
        }
        img_url[i].active = false;
    }
}

static void request_callback(int requestCode, int statusCode, String payload, long time)
{
    Serial.printf("Request Code: %d, Status: %d, Response: %s, Time: %ldms\n",
                  requestCode, statusCode, payload.c_str(), time);

    if (requestCode == 564)
    {
        LVGL_MUTEX_LOCK()
        lv_obj_add_flag(load_spinner, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clean(main_cont);
        
        LVGL_MUTEX_UNLOCK()
        if (statusCode == 200)
        {
            JsonDocument json;
            deserializeJson(json, payload);

            LVGL_MUTEX_LOCK()
            JsonArray array = json["projects"].as<JsonArray>();
            int z = array.size();


            for (int i = 0; i < z; i++)
            {

                if (i >= MAX_IMAGES){
                    break;
                }
                
                JsonObject project = array[i].as<JsonObject>();

                String title = project["title"].as<String>();
                String description = project["description"].as<String>();
                String image = project["image"].as<String>();
                String date = project["date"].as<String>();
                String category = project["category"].as<String>();

                img_url[i].obj = add_item(title.c_str(), category.c_str(), description.c_str(), date.c_str());
                lv_image_set_src(img_url[i].obj, LV_SYMBOL_IMAGE "  Image load requested");
                lv_obj_set_style_text_color(img_url[i].obj, lv_color_hex(0x2F5F5F), LV_PART_MAIN | LV_STATE_DEFAULT);
                img_url[i].url = image;
                img_url[i].width = 290;
                img_url[i].active = true;
            }
            LVGL_MUTEX_UNLOCK()

            Timber.i("Creating image task");

            xTaskCreatePinnedToCore(imageRequest, "Image requests", 8192, NULL, 1, &image_task_handle, 0);
            
        }
        else if (statusCode == -50) {
            LVGL_MUTEX_LOCK()
            add_text("WiFi not connected.");
            LVGL_MUTEX_UNLOCK()
        } else 
        {
            LVGL_MUTEX_LOCK()
            add_text("Load failed");
            LVGL_MUTEX_UNLOCK()
        }
    }
}


void register_fbiego_app()
{
    cm_app_list(fbiego, fbiego_launch_event, register_panel);

    cm_start_tile(fbiego_tile, NULL, fbiego_launch_event, register_start);
}

static void fbiego_launch_event(lv_event_t *e)
{
    if (!fbiego_app_screen)
    {
        Timber.e("fbiego screen NULL");
        fbiego_app_screen_init();
    }

    _ui_screen_change(&fbiego_app_screen, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &fbiego_app_screen_init);
}

static void fbiego_page_events(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_SCREEN_LOADED)
    {
        set_parent(fbiego_app_screen);

        add_text("Loading content");

        startSingleRequest(&projects, request_callback);
    }
    if (event_code == LV_EVENT_SCREEN_UNLOADED)
    {
        Timber.i("Memory: RAM %d, PSRAM %d", ESP.getFreeHeap(), ESP.getFreePsram());

        if (image_task_handle != NULL)
        {
            Timber.e("Image task still running, deleting");
            vTaskDelete(image_task_handle);
            image_task_handle = NULL;
        }

        free_images();

        set_back_handler(NULL);
        lv_obj_delete(fbiego_app_screen);
        fbiego_app_screen = NULL;
        Timber.i("Memory: RAM %d, PSRAM %d", ESP.getFreeHeap(), ESP.getFreePsram());
    }
}

static void add_text(const char *text) {
    lv_obj_t *title_label = lv_label_create(main_cont);
    lv_obj_set_width(title_label, 290);
    lv_obj_set_height(title_label, LV_SIZE_CONTENT);
    lv_obj_set_align(title_label, LV_ALIGN_CENTER);
    lv_label_set_text(title_label, text);
    lv_obj_set_style_text_font(title_label, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
}

static lv_obj_t *add_item(const char *title, const char *category, const char *text, const char *date)
{

    lv_obj_t *panel = lv_obj_create(main_cont);
    lv_obj_set_width(panel, 300);
    lv_obj_set_height(panel, LV_SIZE_CONTENT);
    lv_obj_set_align(panel, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(panel, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(panel, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_remove_flag(panel, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(panel, lv_color_hex(0x333333), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(panel, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(panel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(panel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(panel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(panel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(panel, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *image = lv_image_create(panel);
    // lv_image_set_src(image, &ui_img_battery_png);
    lv_obj_set_width(image, 290);
    lv_obj_set_height(image, LV_SIZE_CONTENT);
    lv_obj_set_align(image, LV_ALIGN_CENTER);
    lv_obj_add_flag(image, LV_OBJ_FLAG_CLICKABLE);    
    lv_obj_remove_flag(image, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t *title_label = lv_label_create(panel);
    lv_obj_set_width(title_label, 290);
    lv_obj_set_height(title_label, LV_SIZE_CONTENT);
    lv_obj_set_align(title_label, LV_ALIGN_CENTER);
    lv_label_set_text(title_label, title);
    lv_obj_set_style_text_font(title_label, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *category_label = lv_label_create(panel);
    lv_obj_set_width(category_label, 290);
    lv_obj_set_height(category_label, LV_SIZE_CONTENT);
    lv_obj_set_align(category_label, LV_ALIGN_CENTER);
    lv_label_set_text(category_label, category);
    lv_obj_set_style_text_font(category_label, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *text_label = lv_label_create(panel);
    lv_obj_set_width(text_label, 290);
    lv_obj_set_height(text_label, LV_SIZE_CONTENT);
    lv_obj_set_align(text_label, LV_ALIGN_CENTER);
    lv_label_set_text(text_label, text);
    lv_obj_set_style_text_font(text_label, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *date_label = lv_label_create(panel);
    lv_obj_set_width(date_label, 290);
    lv_obj_set_height(date_label, LV_SIZE_CONTENT);
    lv_obj_set_align(date_label, LV_ALIGN_CENTER);
    lv_label_set_text(date_label, date);
    lv_obj_set_style_text_font(date_label, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    return image;
}

static void fbiego_app_screen_init(void)
{

    fbiego_app_screen = lv_obj_create(NULL);
    lv_obj_remove_flag(fbiego_app_screen, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(fbiego_app_screen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(fbiego_app_screen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    cm_create_app_title(fbiego_app_screen, "fbiego projects", fbiego.icon);

    main_cont = lv_obj_create(fbiego_app_screen);
    lv_obj_remove_style_all(main_cont);
    lv_obj_set_width(main_cont, 320);
    lv_obj_set_height(main_cont, 370);
    lv_obj_set_y(main_cont, 70);
    lv_obj_set_align(main_cont, LV_ALIGN_TOP_MID);
    lv_obj_set_flex_flow(main_cont, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(main_cont, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_scrollbar_mode(main_cont, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scroll_dir(main_cont, LV_DIR_VER);
    lv_obj_set_style_pad_left(main_cont, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(main_cont, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(main_cont, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(main_cont, 70, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(main_cont, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(main_cont, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    load_spinner = lv_spinner_create(fbiego_app_screen);
    lv_obj_set_width(load_spinner, 100);
    lv_obj_set_height(load_spinner, 100);
    lv_obj_set_align(load_spinner, LV_ALIGN_CENTER);
    lv_obj_remove_flag(load_spinner, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_arc_width(load_spinner, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(load_spinner, 5, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(fbiego_app_screen, fbiego_page_events, LV_EVENT_ALL, NULL);
}

struct FbiegoAppRegister
{
    FbiegoAppRegister()
    {
        AppManager::registerApp(register_fbiego_app);
    }
};

static FbiegoAppRegister fbiego_app;