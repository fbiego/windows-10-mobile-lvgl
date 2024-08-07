

#include "ui_common.h"

void cm_text(lv_obj_t *parent, const char *text)
{
    lv_obj_t *ui_cm_label = lv_label_create(parent);
    lv_obj_set_width(ui_cm_label, 280);
    lv_obj_set_height(ui_cm_label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_cm_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_cm_label, text);
    lv_obj_set_style_text_font(ui_cm_label, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
}

void cm_switch(lv_obj_t *parent, const char* text, bool active, void (*callback)(lv_event_t *e))
{
    lv_obj_t *ui_cm_panel = lv_obj_create(parent);
    lv_obj_set_width(ui_cm_panel, 280);
    lv_obj_set_height(ui_cm_panel, LV_SIZE_CONTENT); /// 50
    lv_obj_set_align(ui_cm_panel, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_cm_panel, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_cm_panel, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
    lv_obj_clear_flag(ui_cm_panel, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_radius(ui_cm_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_cm_panel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_cm_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_cm_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_cm_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_cm_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_cm_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_cm_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_cm_switch = lv_switch_create(ui_cm_panel);
    lv_obj_set_width(ui_cm_switch, 50);
    lv_obj_set_height(ui_cm_switch, 25);
    lv_obj_set_align(ui_cm_switch, LV_ALIGN_CENTER);
    if (active){
        lv_obj_add_state(ui_cm_switch, LV_STATE_CHECKED);
    }
    lv_obj_set_style_bg_color(ui_cm_switch, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_cm_switch, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_cm_switch, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_cm_switch, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_cm_switch, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_cm_switch, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_border_opa(ui_cm_switch, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_border_width(ui_cm_switch, 1, LV_PART_MAIN | LV_STATE_CHECKED);

    lv_obj_t *ui_cm_label = lv_label_create(ui_cm_panel);
    lv_obj_set_width(ui_cm_label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_cm_label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_cm_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_cm_label, text);
    lv_obj_set_style_text_font(ui_cm_label, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_cm_switch, callback, LV_EVENT_VALUE_CHANGED, NULL);

}

void cm_button(lv_obj_t *parent, const char *text)
{
    lv_obj_t *ui_cm_button = lv_btn_create(parent);
    lv_obj_set_width(ui_cm_button, LV_SIZE_CONTENT);  /// 100
    lv_obj_set_height(ui_cm_button, LV_SIZE_CONTENT); /// 50
    lv_obj_set_align(ui_cm_button, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_cm_button, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_clear_flag(ui_cm_button, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_radius(ui_cm_button, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_cm_button, lv_color_hex(0x4A4A4A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_cm_button, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_cm_button, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_cm_button, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_cm_button, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_cm_button, 7, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_cm_label = lv_label_create(ui_cm_button);
    lv_obj_set_width(ui_cm_label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_cm_label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_cm_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_cm_label, text);
    lv_obj_set_style_text_font(ui_cm_label, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
}

void cm_title(lv_obj_t *parent, const char *text)
{
    lv_obj_t *ui_cm_label = lv_label_create(parent);
    lv_obj_set_width(ui_cm_label, 280);
    lv_obj_set_height(ui_cm_label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_cm_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_cm_label, text);
    lv_obj_set_style_text_font(ui_cm_label, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
}

void cm_text_area(lv_obj_t *parent, const char *placeholder, void (*color)(lv_obj_t *obj))
{
    lv_obj_t *ui_cm_text_area = lv_textarea_create(parent);
    lv_obj_set_width(ui_cm_text_area, 300);
    lv_obj_set_height(ui_cm_text_area, LV_SIZE_CONTENT); /// 70
    lv_obj_set_x(ui_cm_text_area, 0);
    lv_obj_set_y(ui_cm_text_area, -145);
    lv_obj_set_align(ui_cm_text_area, LV_ALIGN_CENTER);
    lv_textarea_set_placeholder_text(ui_cm_text_area, placeholder);
    lv_obj_set_style_radius(ui_cm_text_area, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_cm_text_area, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_cm_text_area, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_cm_text_area, lv_color_hex(0x70A2EF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_cm_text_area, 150, LV_PART_MAIN | LV_STATE_DEFAULT);

    color(ui_cm_text_area);

}

void cm_slider(lv_obj_t *parent, int value, int min, int max, void (*callback)(lv_event_t *e))
{
    lv_obj_t *ui_cm_slider = lv_slider_create(parent);
    lv_slider_set_range(ui_cm_slider, min, max);
    lv_slider_set_value(ui_cm_slider, value, LV_ANIM_OFF);
    if (lv_slider_get_mode(ui_cm_slider) == LV_SLIDER_MODE_RANGE)
        lv_slider_set_left_value(ui_cm_slider, 0, LV_ANIM_OFF);
    lv_obj_set_width(ui_cm_slider, 270);
    lv_obj_set_height(ui_cm_slider, 2);
    lv_obj_set_align(ui_cm_slider, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(ui_cm_slider, lv_color_hex(0x646464), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_cm_slider, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_cm_slider, callback, LV_EVENT_VALUE_CHANGED, NULL);

}

void cm_panel_space(lv_obj_t *parent)
{
    lv_obj_t *ui_cm_panel = lv_obj_create(parent);
    lv_obj_set_width(ui_cm_panel, 280);
    lv_obj_set_height(ui_cm_panel, 10);
    lv_obj_set_align(ui_cm_panel, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_cm_panel, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_cm_panel, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
    lv_obj_clear_flag(ui_cm_panel, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_radius(ui_cm_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_cm_panel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_cm_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_cm_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_cm_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_cm_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_cm_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_cm_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
}

void cm_bar(lv_obj_t *parent, int value)
{
    lv_obj_t *ui_cm_panel = lv_obj_create(parent);
    lv_obj_set_width(ui_cm_panel, 280);
    lv_obj_set_height(ui_cm_panel, LV_SIZE_CONTENT); /// 50
    lv_obj_set_align(ui_cm_panel, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_cm_panel, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_cm_panel, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_clear_flag(ui_cm_panel, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_radius(ui_cm_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_cm_panel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_cm_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_cm_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_cm_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_cm_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_cm_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_cm_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_label = lv_label_create(ui_cm_panel);
    lv_obj_set_width(ui_label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_label, LV_ALIGN_CENTER);
    lv_label_set_text_fmt(ui_label, "%d%%", value);
    lv_obj_set_style_text_font(ui_label, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_label, -5, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_bar = lv_bar_create(ui_cm_panel);
    lv_bar_set_value(ui_bar, value, LV_ANIM_OFF);
    lv_bar_set_start_value(ui_bar, 0, LV_ANIM_OFF);
    lv_obj_set_width(ui_bar, 270);
    lv_obj_set_height(ui_bar, 7);
    lv_obj_set_align(ui_bar, LV_ALIGN_CENTER);
    lv_obj_set_style_radius(ui_bar, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_bar, lv_color_hex(0x3F3F3F), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_bar, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_bar, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
}

void cm_dropdown(lv_obj_t *parent, const char* options, int selected, int width, void (*callback)(lv_event_t *e))
{
    lv_obj_t *ui_cm_dropdown = lv_dropdown_create(parent);
    lv_dropdown_set_options(ui_cm_dropdown, options);
    lv_dropdown_set_selected(ui_cm_dropdown, selected);
    lv_obj_set_width(ui_cm_dropdown, width);
    lv_obj_set_height(ui_cm_dropdown, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_cm_dropdown, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_cm_dropdown, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_set_style_radius(ui_cm_dropdown, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_cm_dropdown, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_cm_dropdown, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_cm_dropdown, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_cm_dropdown, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_cm_dropdown, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_radius(lv_dropdown_get_list(ui_cm_dropdown), 0,  LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(lv_dropdown_get_list(ui_cm_dropdown), lv_color_hex(0x000000),  LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(lv_dropdown_get_list(ui_cm_dropdown), 255,  LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_cm_dropdown, callback, LV_EVENT_VALUE_CHANGED, NULL);
}


void cm_user_list(lv_obj_t *parent, user_info_t user)
{
    lv_obj_t *ui_cm_panel = lv_obj_create(parent);
    lv_obj_set_width(ui_cm_panel, 280);
    lv_obj_set_height(ui_cm_panel, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_cm_panel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_cm_panel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_cm_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_cm_panel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_cm_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_cm_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_cm_panel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_cm_panel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_cm_panel, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_cm_panel, 7, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_cm_avatar = lv_img_create(ui_cm_panel);
    lv_img_set_src(ui_cm_avatar, user.icon);
    lv_obj_set_width(ui_cm_avatar, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_cm_avatar, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_cm_avatar, LV_ALIGN_LEFT_MID);
    lv_obj_add_flag(ui_cm_avatar, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_cm_avatar, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    lv_obj_t *ui_cm_username = lv_label_create(ui_cm_panel);
    lv_obj_set_width(ui_cm_username, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_cm_username, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_cm_username, LV_ALIGN_LEFT_MID);
    lv_obj_set_x(ui_cm_username, 50);
    lv_obj_set_y(ui_cm_username, 0);
    lv_label_set_text(ui_cm_username, user.username);
    lv_obj_set_style_text_font(ui_cm_username, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);

}

void cm_quick_action(lv_obj_t *parent, const char* name, const lv_img_dsc_t *icon, bool checkable)
{
    lv_obj_t *ui_cm_button = lv_btn_create(parent);
    lv_obj_set_width(ui_cm_button, 58);
    lv_obj_set_height(ui_cm_button, 40);
    lv_obj_set_x(ui_cm_button, -56);
    lv_obj_set_y(ui_cm_button, -23);
    lv_obj_set_align(ui_cm_button, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_cm_button, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_cm_button, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_add_flag(ui_cm_button, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    if (checkable){
        lv_obj_add_flag(ui_cm_button, LV_OBJ_FLAG_CHECKABLE );     /// Flags
        lv_obj_add_state(ui_cm_button, LV_STATE_CHECKED);
    }
    lv_obj_clear_flag(ui_cm_button, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_cm_button, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_cm_button, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_cm_button, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_cm_button, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_cm_button, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_cm_button, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_cm_button, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui_cm_button, lv_color_hex(0x444444), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_cm_button, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_border_width(ui_cm_button, 0, LV_PART_MAIN | LV_STATE_CHECKED);

    lv_obj_t *ui_cm_image = lv_img_create(ui_cm_button);
    lv_img_set_src(ui_cm_image, icon);
    lv_obj_set_width(ui_cm_image, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_cm_image, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_cm_image, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_cm_image, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_cm_image, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    lv_obj_t *ui_Label30 = lv_label_create(ui_cm_button);
    lv_obj_set_width(ui_Label30, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label30, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label30, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label30, name);
    lv_obj_set_style_text_font(ui_Label30, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
}

void cm_start_tile(start_tile_t tile, void(*callback)(live_obj_t l), void(*launcher)(lv_event_t *e), void(*start)(lv_obj_t *obj))
{
    lv_obj_t *ui_cm_panel = lv_obj_create(ui_startPanel);
    lv_obj_set_width(ui_cm_panel, tile.wide ? 205 : 100);
    lv_obj_set_height(ui_cm_panel, 76);
    lv_obj_set_align(ui_cm_panel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_cm_panel, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_radius(ui_cm_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_cm_panel, lv_color_hex(0x136DC8), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_cm_panel, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_cm_panel, tile.app.icon, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_cm_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_cm_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_cm_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_cm_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_cm_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_cm_label = lv_label_create(ui_cm_panel);
    lv_obj_set_width(ui_cm_label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_cm_label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_cm_label, LV_ALIGN_BOTTOM_LEFT);
    lv_label_set_long_mode(ui_cm_label, LV_LABEL_LONG_CLIP);
    lv_label_set_text(ui_cm_label, tile.app.name);
    lv_obj_set_style_text_font(ui_cm_label, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_cm_label, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_cm_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_cm_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_cm_label, 5, LV_PART_MAIN | LV_STATE_DEFAULT);

    if (tile.dir != CM_LIVE_NONE && tile.live != NULL)
    {
        lv_obj_t *ui_cm_image = lv_img_create(ui_cm_panel);
        lv_img_set_src(ui_cm_image, tile.live);
        lv_obj_set_width(ui_cm_image, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_cm_image, LV_SIZE_CONTENT); /// 1
        lv_obj_set_x(ui_cm_image, tile.dir == CM_LIVE_VERTICAL ? 0 : 100);
        lv_obj_set_y(ui_cm_image, tile.dir == CM_LIVE_VERTICAL ? 76 : 0);
        lv_obj_set_align(ui_cm_image, tile.dir == CM_LIVE_VERTICAL ? LV_ALIGN_TOP_MID : LV_ALIGN_LEFT_MID);
        lv_obj_add_flag(ui_cm_image, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
        lv_obj_clear_flag(ui_cm_image, LV_OBJ_FLAG_SCROLLABLE); /// Flags
        live_obj_t t = {ui_cm_image, tile.dir};
        callback(t);
    }

    start(ui_cm_panel);

    lv_obj_add_event_cb(ui_cm_panel, launcher, LV_EVENT_CLICKED, (void*)tile.app.code);


}

void cm_app_list(app_info_t app, void (*launcher)(lv_event_t * e), void(*panel)(lv_obj_t *obj))
{
    lv_obj_t *ui_cm_panel = lv_obj_create(ui_appsListPanel);
    lv_obj_set_width(ui_cm_panel, 320);
    lv_obj_set_height(ui_cm_panel, 50);
    lv_obj_set_align(ui_cm_panel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_cm_panel, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_radius(ui_cm_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_cm_panel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_cm_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_cm_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_cm_panel_icon = lv_obj_create(ui_cm_panel);
    lv_obj_set_width(ui_cm_panel_icon, 50);
    lv_obj_set_height(ui_cm_panel_icon, 50);
    lv_obj_set_align(ui_cm_panel_icon, LV_ALIGN_LEFT_MID);
    lv_obj_clear_flag(ui_cm_panel_icon, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_radius(ui_cm_panel_icon, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_cm_panel_icon, lv_color_hex(0x1390EA), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_cm_panel_icon, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_cm_panel_icon, app.icon, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_cm_panel_icon, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_cm_label = lv_label_create(ui_cm_panel);
    lv_obj_set_width(ui_cm_label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_cm_label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_cm_label, 65);
    lv_obj_set_y(ui_cm_label, 0);
    lv_obj_set_align(ui_cm_label, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_cm_label, app.name);
    lv_obj_set_style_text_font(ui_cm_label, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    panel(ui_cm_panel_icon);

    lv_obj_add_event_cb(ui_cm_panel, launcher, LV_EVENT_CLICKED, (void*)app.code);

}

void cm_settings_list(lv_obj_t *parent, settings_info_t setting, void (*launcher)(lv_event_t * e), void(*img)(lv_obj_t *obj))
{
    lv_obj_t *ui_cm_panel = lv_obj_create(parent);
    lv_obj_set_width(ui_cm_panel, 320);
    lv_obj_set_height(ui_cm_panel, 50);
    lv_obj_set_align(ui_cm_panel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_cm_panel, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_radius(ui_cm_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_cm_panel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_cm_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_cm_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_cm_icon = lv_img_create(ui_cm_panel);
    lv_img_set_src(ui_cm_icon, setting.icon);
    lv_obj_set_width(ui_cm_icon, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_cm_icon, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_cm_icon, 5);
    lv_obj_set_y(ui_cm_icon, 0);
    lv_obj_set_align(ui_cm_icon, LV_ALIGN_LEFT_MID);
    lv_obj_add_flag(ui_cm_icon, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_cm_icon, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_img_recolor(ui_cm_icon, lv_color_hex(0x2D87E1), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui_cm_icon, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_cm_title = lv_label_create(ui_cm_panel);
    lv_obj_set_width(ui_cm_title, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_cm_title, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_cm_title, 50);
    lv_obj_set_y(ui_cm_title, -12);
    lv_obj_set_align(ui_cm_title, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_cm_title, setting.title);
    lv_obj_set_style_text_font(ui_cm_title, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_cm_info = lv_label_create(ui_cm_panel);
    lv_obj_set_width(ui_cm_info, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_cm_info, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_cm_info, 50);
    lv_obj_set_y(ui_cm_info, 10);
    lv_obj_set_align(ui_cm_info, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_cm_info, setting.desc);
    lv_obj_set_style_text_font(ui_cm_info, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    img(ui_cm_icon);

    lv_obj_add_event_cb(ui_cm_panel, launcher, LV_EVENT_CLICKED, (void*)setting.code);
}

void cm_accent_color(lv_obj_t *parent, accent_color_t color, void (*callback)(lv_event_t *e))
{
    lv_obj_t *ui_cm_color = lv_obj_create(parent);
    lv_obj_set_width(ui_cm_color, 50);
    lv_obj_set_height(ui_cm_color, 50);
    lv_obj_set_align(ui_cm_color, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_cm_color, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_cm_color, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_cm_color, lv_color_hex(color.color), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_cm_color, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_cm_color, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_cm_color, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_outline_color(ui_cm_color, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_outline_opa(ui_cm_color, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_outline_width(ui_cm_color, 5, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_outline_pad(ui_cm_color, 0, LV_PART_MAIN | LV_STATE_PRESSED);

    lv_obj_add_event_cb(ui_cm_color, callback, LV_EVENT_CLICKED, (void*)(uint64_t)color.color);
}

void cm_image_select(lv_obj_t *parent, const lv_img_dsc_t *img, uint64_t index, void (*callback)(lv_event_t *e))
{
    lv_obj_t *ui_cm_panel = lv_obj_create(parent);
    lv_obj_set_width(ui_cm_panel, 50);
    lv_obj_set_height(ui_cm_panel, 100);
    lv_obj_set_x(ui_cm_panel, 0);
    lv_obj_set_y(ui_cm_panel, 32);
    lv_obj_set_align(ui_cm_panel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_cm_panel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_cm_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_cm_panel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_cm_panel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_cm_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_cm_panel, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_outline_color(ui_cm_panel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_outline_opa(ui_cm_panel, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_outline_width(ui_cm_panel, 5, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_outline_pad(ui_cm_panel, 0, LV_PART_MAIN | LV_STATE_PRESSED);

    lv_obj_t *ui_cm_image = lv_img_create(ui_cm_panel);
    lv_img_set_src(ui_cm_image, img);
    lv_obj_set_width(ui_cm_image, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_cm_image, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_cm_image, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_cm_image, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_cm_image, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_cm_image, 50);

    lv_obj_add_event_cb(ui_cm_panel, callback, LV_EVENT_CLICKED, (void*)index);
}

void set_parent(lv_obj_t *parent)
{
    lv_obj_set_parent(ui_cortanaPanel, parent);
    lv_obj_set_parent(ui_navPanel, parent);
    lv_obj_set_parent(ui_lockScreenPanel, parent);
    lv_obj_set_parent(ui_notificationPanel, parent);
    lv_obj_set_parent(ui_statusPanel, parent);
    lv_obj_set_parent(ui_alertPanel, parent);
}

