
#include <lvgl.h>
#include "../app_hal.h"
#include "ui/ui.h"
#include <ArduinoJson.h>
#include <Timber.h>

#include "../../core/requests.h"
#include "../../core/app_manager.h"

static lv_obj_t *blog_app_screen;
static lv_obj_t *main_cont;
static lv_obj_t *blog_list;
static lv_obj_t *blog_content;
static lv_obj_t *load_spinner;

#define MAX_IMAGES 7

static TaskHandle_t image_task_handle = NULL;

LV_IMAGE_DECLARE(ui_img_internet_png);

static app_info_t blog = {
    .code = 0x0000,
    .name = "Arduino Blog",
    .icon = &ui_img_internet_png};

static start_tile_t blog_tile = {
    .app = blog,
    .wide = false,
    .live = NULL,
    .dir = CM_LIVE_NONE};

static Request list = {
    .url = "http://iot.fbiego.com/arduino/blog",
    .code = 344,
    .method = false,
    .data = "",
    .active = true};

static Request single = {
    .url = "http://iot.fbiego.com/arduino/blog?id=",
    .code = 345,
    .method = false,
    .data = "",
    .active = true};

static ImageUrl img_url[MAX_IMAGES];

static void blog_app_screen_init(void);
static void add_blog_title(lv_obj_t *parent, const char *title);
static void add_blog_item(lv_obj_t *parent, const char *title, int64_t code, void (*callback)(lv_event_t *e));
static void add_blog_text(lv_obj_t *parent, const char *text);
static void load_single_blog(lv_event_t *e);
static void close_single_blog(lv_event_t *e);
static void load_image(uint8_t index);
static void back_button_handler();


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

    if (requestCode == 344)
    {
        LVGL_MUTEX_LOCK()
        lv_obj_add_flag(load_spinner, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clean(blog_list);
        if (statusCode == 200)
        {
            JsonDocument json;
            deserializeJson(json, payload);
            if (json["success"])
            {
                JsonArray array = json["article"].as<JsonArray>();
                for (JsonVariant j : array)
                {
                    JsonObject v = j.as<JsonObject>();
                    String text = v["text"].as<String>();
                    int64_t id = v["id"].as<int64_t>();
                    String link = v["image"].as<String>();
                    add_blog_item(blog_list, text.c_str(), id, load_single_blog);
                }
            }
            else
            {
                add_blog_title(blog_list, "Load failed. Unsuccessful");
            }
        }
        else if (statusCode == -50)
        {
            add_blog_title(blog_list, "WiFi not connected");
        } else
        {
            add_blog_title(blog_list, "Load failed");
        }
        LVGL_MUTEX_UNLOCK()
    }
    if (requestCode == 345)
    {
        LVGL_MUTEX_LOCK()
        lv_obj_add_flag(load_spinner, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clean(blog_content);
        // add_blog_item(blog_content, "Back", 0, close_single_blog);
        LVGL_MUTEX_UNLOCK()
        if (statusCode == 200)
        {
            JsonDocument json;
            deserializeJson(json, payload);
            if (json["success"])
            {
                LVGL_MUTEX_LOCK()
                String title = json["title"].as<String>();
                add_blog_title(blog_content, title.c_str());

                JsonArray array = json["text"].as<JsonArray>();   // text
                JsonArray images = json["image"].as<JsonArray>(); // images
                int z = array.size();
                int y = images.size();
                int gap = (z + 1) / (y + 1);
                int count = 0;

                Timber.i("Paragraphs %d images %d", z, y);

                for (int i = 0; i < z; i++)
                {
                    String p = array[i].as<String>();
                    add_blog_text(blog_content, p.c_str());

                    if (count < y && (i + 1) % gap == 0)
                    {
                        // image
                        if (count < MAX_IMAGES)
                        {
                            String link = images[count].as<String>();
                            img_url[count].obj = lv_image_create(blog_content);
                            lv_image_set_src(img_url[count].obj, LV_SYMBOL_IMAGE "  Image load requested");
                            lv_obj_set_style_text_color(img_url[count].obj, lv_color_hex(0x2F5F5F), LV_PART_MAIN | LV_STATE_DEFAULT);

                            img_url[count].url = link;
                            img_url[count].width = 300;
                            img_url[count].active = true;

                        }
                        count++;
                    }
                }
                LVGL_MUTEX_UNLOCK()

                Timber.i("Creating image task");

                xTaskCreatePinnedToCore(imageRequest, "Image requests", 8192, NULL, 1, &image_task_handle, 0);
            }
            else
            {
                LVGL_MUTEX_LOCK()
                add_blog_title(blog_content, "Load failed. Unsuccessful");
                LVGL_MUTEX_UNLOCK()
            }
        }
        else if (statusCode == -50)
        {
            LVGL_MUTEX_LOCK()
            add_blog_title(blog_content, "WiFi not connected");
            LVGL_MUTEX_UNLOCK()
        } else
        {
            LVGL_MUTEX_LOCK()
            add_blog_title(blog_content, "Load failed");
            LVGL_MUTEX_UNLOCK()
        }
    }
}

static void blog_launch_event(lv_event_t *e)
{
    if (!blog_app_screen)
    {
        Timber.e("Blog screen NULL");
        blog_app_screen_init();
    }

    _ui_screen_change(&blog_app_screen, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &blog_app_screen_init);
}

static void blog_page_events(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_SCREEN_LOADED)
    {
        set_parent(blog_app_screen);

        lv_obj_remove_flag(load_spinner, LV_OBJ_FLAG_HIDDEN);
        lv_obj_remove_flag(blog_list, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(blog_content, LV_OBJ_FLAG_HIDDEN);

        add_blog_text(blog_list, "Loading content");

        startSingleRequest(&list, request_callback);
        
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
        lv_obj_delete(blog_app_screen);
        blog_app_screen = NULL;
        Timber.i("Memory: RAM %d, PSRAM %d", ESP.getFreeHeap(), ESP.getFreePsram());
    }
}

static void load_single_blog(lv_event_t *e)
{
    int64_t code = (int64_t)lv_event_get_user_data(e);
    lv_obj_clean(blog_content);
    lv_obj_remove_flag(load_spinner, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(blog_list, LV_OBJ_FLAG_HIDDEN);
    lv_obj_remove_flag(blog_content, LV_OBJ_FLAG_HIDDEN);

    set_back_handler(back_button_handler);

    if (image_task_handle != NULL)
    {
        Timber.e("Image task still running, deleting");
        vTaskDelete(image_task_handle);
        image_task_handle = NULL;
    }

    free_images();

    single.url = "http://iot.fbiego.com/arduino/blog?id=" + String(code);
    single.active = true;

    startSingleRequest(&single, request_callback);
}

static void back_button_handler()
{
    lv_obj_add_flag(load_spinner, LV_OBJ_FLAG_HIDDEN);
    lv_obj_remove_flag(blog_list, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(blog_content, LV_OBJ_FLAG_HIDDEN);

    if (image_task_handle != NULL)
    {
        Timber.e("Image task still running");
        vTaskDelete(image_task_handle);
        image_task_handle = NULL;
    }
    set_back_handler(NULL);
}

static void close_single_blog(lv_event_t *e)
{
    back_button_handler();
}

void register_blog_app()
{
    cm_app_list(blog, blog_launch_event, register_panel);

    cm_start_tile(blog_tile, NULL, blog_launch_event, register_start);
}

static void add_blog_item(lv_obj_t *parent, const char *title, int64_t code, void (*callback)(lv_event_t *e))
{
    lv_obj_t *ui_blogLabel = lv_label_create(parent);
    lv_obj_set_width(ui_blogLabel, 300);
    lv_obj_set_height(ui_blogLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_blogLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_blogLabel, title);
    lv_obj_add_flag(ui_blogLabel, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_text_font(ui_blogLabel, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_blogLabel, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_blogLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_blogLabel, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_blogLabel, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_blogLabel, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_blogLabel, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_blogLabel, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_blogLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui_blogLabel, 150, LV_PART_MAIN | LV_STATE_PRESSED);

    lv_obj_add_event_cb(ui_blogLabel, callback, LV_EVENT_CLICKED, (void *)code);
}

static void add_blog_title(lv_obj_t *parent, const char *title)
{
    lv_obj_t *ui_blogTitle = lv_label_create(parent);
    lv_obj_set_width(ui_blogTitle, 300);
    lv_obj_set_height(ui_blogTitle, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_blogTitle, LV_ALIGN_CENTER);
    lv_label_set_text(ui_blogTitle, title);
    lv_obj_set_style_text_font(ui_blogTitle, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_blogTitle, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_blogTitle, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_blogTitle, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_blogTitle, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_blogTitle, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_blogTitle, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_blogTitle, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_blogTitle, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
}

static void add_blog_text(lv_obj_t *parent, const char *text)
{
    lv_obj_t *ui_blogTitle1 = lv_label_create(parent);
    lv_obj_set_width(ui_blogTitle1, 300);
    lv_obj_set_height(ui_blogTitle1, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_blogTitle1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_blogTitle1, text);
    lv_obj_set_style_text_font(ui_blogTitle1, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
}

static void blog_app_screen_init(void)
{
    blog_app_screen = lv_obj_create(NULL);
    lv_obj_remove_flag(blog_app_screen, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(blog_app_screen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(blog_app_screen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    cm_create_app_title(blog_app_screen, blog.name, blog.icon);

    main_cont = lv_obj_create(blog_app_screen);
    lv_obj_remove_style_all(main_cont);
    lv_obj_set_width(main_cont, 320);
    lv_obj_set_height(main_cont, 370);
    lv_obj_set_y(main_cont, 70);
    lv_obj_set_align(main_cont, LV_ALIGN_TOP_MID);
    lv_obj_remove_flag(main_cont, LV_OBJ_FLAG_SCROLLABLE);

    blog_list = lv_obj_create(main_cont);
    lv_obj_remove_style_all(blog_list);
    lv_obj_set_width(blog_list, 320);
    lv_obj_set_height(blog_list, 370);
    lv_obj_set_align(blog_list, LV_ALIGN_TOP_MID);
    lv_obj_set_flex_flow(blog_list, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(blog_list, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);
    lv_obj_add_flag(blog_list, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_scrollbar_mode(blog_list, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scroll_dir(blog_list, LV_DIR_VER);
    lv_obj_set_style_pad_left(blog_list, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(blog_list, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(blog_list, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(blog_list, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(blog_list, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(blog_list, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    blog_content = lv_obj_create(main_cont);
    lv_obj_remove_style_all(blog_content);
    lv_obj_set_width(blog_content, 320);
    lv_obj_set_height(blog_content, 370);
    lv_obj_set_align(blog_content, LV_ALIGN_TOP_MID);
    lv_obj_set_flex_flow(blog_content, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(blog_content, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_scrollbar_mode(blog_content, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scroll_dir(blog_content, LV_DIR_VER);
    lv_obj_set_style_pad_left(blog_content, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(blog_content, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(blog_content, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(blog_content, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(blog_content, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(blog_content, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_flag(blog_content, LV_OBJ_FLAG_HIDDEN);

    load_spinner = lv_spinner_create(main_cont);
    lv_obj_set_width(load_spinner, 100);
    lv_obj_set_height(load_spinner, 100);
    lv_obj_set_align(load_spinner, LV_ALIGN_CENTER);
    lv_obj_remove_flag(load_spinner, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_arc_width(load_spinner, 5, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_arc_width(load_spinner, 5, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(blog_app_screen, blog_page_events, LV_EVENT_ALL, NULL);

    Timber.i("Arduino Blog app created");
}

struct BlogAppRegister
{
    BlogAppRegister()
    {
        AppManager::registerApp(register_blog_app);
    }
};

static BlogAppRegister blog_app;