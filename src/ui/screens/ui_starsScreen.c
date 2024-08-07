// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.1
// LVGL version: 8.3.11
// Project name: W10M

#include "../ui.h"

void ui_starsScreen_screen_init(void)
{
    ui_starsScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_starsScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_starsScreen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_starsScreen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_starsTitlePanel = lv_obj_create(ui_starsScreen);
    lv_obj_set_width(ui_starsTitlePanel, 320);
    lv_obj_set_height(ui_starsTitlePanel, 70);
    lv_obj_set_align(ui_starsTitlePanel, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(ui_starsTitlePanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_starsTitlePanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_starsTitlePanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_starsTitleName = lv_label_create(ui_starsTitlePanel);
    lv_obj_set_width(ui_starsTitleName, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_starsTitleName, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_starsTitleName, 52);
    lv_obj_set_y(ui_starsTitleName, 10);
    lv_obj_set_align(ui_starsTitleName, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_starsTitleName, "Github Stars");
    lv_obj_set_style_text_font(ui_starsTitleName, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_starsTitleIcon = lv_img_create(ui_starsTitlePanel);
    lv_img_set_src(ui_starsTitleIcon, &ui_img_stars_ic_png);
    lv_obj_set_width(ui_starsTitleIcon, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_starsTitleIcon, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_starsTitleIcon, 10);
    lv_obj_set_y(ui_starsTitleIcon, 10);
    lv_obj_set_align(ui_starsTitleIcon, LV_ALIGN_LEFT_MID);
    lv_obj_add_flag(ui_starsTitleIcon, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_starsTitleIcon, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_img_recolor(ui_starsTitleIcon, lv_color_hex(0x2062E3), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui_starsTitleIcon, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_starsMainPanel = lv_obj_create(ui_starsScreen);
    lv_obj_set_width(ui_starsMainPanel, 320);
    lv_obj_set_height(ui_starsMainPanel, 410);
    lv_obj_set_x(ui_starsMainPanel, 0);
    lv_obj_set_y(ui_starsMainPanel, 70);
    lv_obj_set_align(ui_starsMainPanel, LV_ALIGN_TOP_MID);
    lv_obj_set_flex_flow(ui_starsMainPanel, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_starsMainPanel, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_set_scrollbar_mode(ui_starsMainPanel, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_radius(ui_starsMainPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_starsMainPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_starsMainPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_starsMainPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_starsMainPanel, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_starsMainPanel, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_starsMainPanel, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_starsMainPanel, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(ui_starsMainPanel, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(ui_starsMainPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label23 = lv_label_create(ui_starsMainPanel);
    lv_obj_set_width(ui_Label23, 280);
    lv_obj_set_height(ui_Label23, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label23, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label23,
                      "The list below is generated before compilation from Github stars API using a pre-build script on PlatformIO IDE.");
    lv_obj_set_style_text_font(ui_Label23, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label7 = lv_label_create(ui_starsMainPanel);
    lv_obj_set_width(ui_Label7, 280);
    lv_obj_set_height(ui_Label7, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label7, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label7, "Total Stars: 2");
    lv_obj_set_style_text_font(ui_Label7, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);


    lv_obj_add_event_cb(ui_starsScreen, ui_event_screen_load, LV_EVENT_SCREEN_LOADED, NULL);

}