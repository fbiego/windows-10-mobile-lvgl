

#ifndef _W10M_UI_COMMON_H
#define _W10M_UI_COMMON_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "ui.h"

typedef enum
{
    CM_LIVE_NONE = -1,
    CM_LIVE_VERTICAL,
    CM_LIVE_HORIZONTAL
} cm_live_dir_t;

typedef enum
{
    TM_BG_COLOR = (1 << 0),
    TM_BORDER_COLOR = (1 << 1),
    TM_IMAGE_TINT = (1 << 2),

    TM_ALL = 0xFF
} theme_type_t;

typedef struct _app_info_t
{
    uint64_t code;
    const char *name;
    const lv_img_dsc_t *icon;
} app_info_t;

typedef struct _start_tile_t
{
    app_info_t app;
    bool wide;
    const lv_img_dsc_t *live;
    cm_live_dir_t dir;
} start_tile_t;

typedef struct _user_info_t
{
    const char *username;
    const lv_img_dsc_t *icon;
} user_info_t;

typedef struct _live_obj_t
{
    lv_obj_t *obj;
    cm_live_dir_t dir;
} live_obj_t;

typedef struct _settings_info_t
{
    uint64_t code;
    const char *title;
    const char *desc;
    const lv_img_dsc_t *icon;
} settings_info_t;

typedef struct _accent_color_t
{
    const char* name;
    uint32_t color;
} accent_color_t;

typedef struct _themeable_t
{
    lv_obj_t *obj;
    theme_type_t type;
} themeable_t;

void cm_text(lv_obj_t *parent, const char *text);
void cm_switch(lv_obj_t *parent, const char* text, bool active, void (*callback)(lv_event_t *e));
void cm_button(lv_obj_t *parent, const char *text);
void cm_title(lv_obj_t *parent, const char *text);
void cm_text_area(lv_obj_t *parent, const char *placeholder, void (*color)(lv_obj_t *obj));
void cm_slider(lv_obj_t *parent, int value, int min, int max, void (*callback)(lv_event_t *e));
void cm_panel_space(lv_obj_t *parent);
void cm_bar(lv_obj_t *parent, int value);
void cm_dropdown(lv_obj_t *parent, const char* options, int selected, int width, void (*callback)(lv_event_t *e));
void cm_user_list(lv_obj_t *parent, user_info_t user);

void cm_quick_action(lv_obj_t *parent, const char *name, const lv_img_dsc_t *icon, bool checkable);

void cm_start_tile(start_tile_t tile, void(*callback)(live_obj_t l), void (*launcher)(lv_event_t * e), void(*start)(lv_obj_t *obj));
void cm_app_list(app_info_t app, void(*launcher)(lv_event_t *e), void(*panel)(lv_obj_t *obj));

void cm_settings_list(lv_obj_t *parent, settings_info_t setting, void (*launcher)(lv_event_t * e), void(*img)(lv_obj_t *obj));
void cm_accent_color(lv_obj_t *parent, accent_color_t color, void (*callback)(lv_event_t *e));
void cm_image_select(lv_obj_t *parent, const lv_img_dsc_t *img, uint64_t index, void (*callback)(lv_event_t *e));

void set_parent(lv_obj_t *parent);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif