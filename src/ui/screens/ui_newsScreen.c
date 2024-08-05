// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.1
// LVGL version: 8.3.11
// Project name: W10M

#include "../ui.h"

void ui_newsScreen_screen_init(void)
{
    ui_newsScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_newsScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_appTitlePanel1 = lv_obj_create(ui_newsScreen);
    lv_obj_set_width(ui_appTitlePanel1, 320);
    lv_obj_set_height(ui_appTitlePanel1, 70);
    lv_obj_set_align(ui_appTitlePanel1, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(ui_appTitlePanel1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_appTitlePanel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_appTitlePanel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_appTitleName1 = lv_label_create(ui_appTitlePanel1);
    lv_obj_set_width(ui_appTitleName1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_appTitleName1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_appTitleName1, 52);
    lv_obj_set_y(ui_appTitleName1, 10);
    lv_obj_set_align(ui_appTitleName1, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_appTitleName1, "News");
    lv_obj_set_style_text_font(ui_appTitleName1, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_appTitleIcon1 = lv_img_create(ui_appTitlePanel1);
    lv_img_set_src(ui_appTitleIcon1, &ui_img_news_ic_png);
    lv_obj_set_width(ui_appTitleIcon1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_appTitleIcon1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_appTitleIcon1, 10);
    lv_obj_set_y(ui_appTitleIcon1, 10);
    lv_obj_set_align(ui_appTitleIcon1, LV_ALIGN_LEFT_MID);
    lv_obj_add_flag(ui_appTitleIcon1, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_appTitleIcon1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_img_recolor(ui_appTitleIcon1, lv_color_hex(0x2062E3), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui_appTitleIcon1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_settingsMainPanel1 = lv_obj_create(ui_newsScreen);
    lv_obj_set_width(ui_settingsMainPanel1, 320);
    lv_obj_set_height(ui_settingsMainPanel1, 410);
    lv_obj_set_x(ui_settingsMainPanel1, 0);
    lv_obj_set_y(ui_settingsMainPanel1, 70);
    lv_obj_set_align(ui_settingsMainPanel1, LV_ALIGN_TOP_MID);
    lv_obj_set_flex_flow(ui_settingsMainPanel1, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_settingsMainPanel1, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_scrollbar_mode(ui_settingsMainPanel1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scroll_dir(ui_settingsMainPanel1, LV_DIR_VER);
    lv_obj_set_style_radius(ui_settingsMainPanel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_settingsMainPanel1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_settingsMainPanel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_settingsMainPanel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_settingsMainPanel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_settingsMainPanel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_settingsMainPanel1, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_settingsMainPanel1, 50, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_radius(ui_settingsMainPanel1, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_settingsMainPanel1, lv_color_hex(0xFFFFFF), LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_settingsMainPanel1, 100, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

    ui_Panel25 = lv_obj_create(ui_settingsMainPanel1);
    lv_obj_set_width(ui_Panel25, 280);
    lv_obj_set_height(ui_Panel25, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_align(ui_Panel25, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_Panel25, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_Panel25, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Panel25, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Panel25, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Panel25, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel25, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Panel25, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Panel25, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Panel25, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_Panel25, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Panel25, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Panel25, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Panel25, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Panel25, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label2 = lv_label_create(ui_Panel25);
    lv_obj_set_width(ui_Label2, 280);
    lv_obj_set_height(ui_Label2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label2, "Windows 10 Mobile UI Designed with SquareLine Studio and LVGL");
    lv_obj_set_style_text_font(ui_Label2, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Panel1 = lv_obj_create(ui_Panel25);
    lv_obj_set_width(ui_Panel1, 205);
    lv_obj_set_height(ui_Panel1, 76);
    lv_obj_set_align(ui_Panel1, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Panel1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Panel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Panel1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Panel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Panel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Panel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Panel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Panel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Image13 = lv_img_create(ui_Panel1);
    lv_img_set_src(ui_Image13, &ui_img_news_image_png);
    lv_obj_set_width(ui_Image13, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Image13, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Image13, LV_ALIGN_TOP_MID);
    lv_obj_add_flag(ui_Image13, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image13, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label42 = lv_label_create(ui_Panel25);
    lv_obj_set_width(ui_Label42, 280);
    lv_obj_set_height(ui_Label42, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label42, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label42,
                      "The Windows 10 Mobile UI project showcases the nostalgic Lumia experience on the ESP32 using the powerful LVGL graphics library. This revamped user interface, designed with SquareLine Studio, offers a blend of nostalgia and modern functionality, bringing the classic Windows 10 Mobile feel to new hardware.\n-----------------------------\nGithub: fbiego windows-10-mobile-lvgl");
    lv_obj_set_style_text_font(ui_Label42, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Panel29 = lv_obj_create(ui_settingsMainPanel1);
    lv_obj_set_width(ui_Panel29, 280);
    lv_obj_set_height(ui_Panel29, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_align(ui_Panel29, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_Panel29, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_Panel29, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Panel29, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Panel29, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Panel29, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel29, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Panel29, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Panel29, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Panel29, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_Panel29, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Panel29, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Panel29, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Panel29, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Panel29, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label1 = lv_label_create(ui_Panel29);
    lv_obj_set_width(ui_Label1, 280);
    lv_obj_set_height(ui_Label1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label1, "LVGL Unveils Vibrant New Website and Logo");
    lv_obj_set_style_text_font(ui_Label1, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Panel31 = lv_obj_create(ui_Panel29);
    lv_obj_set_width(ui_Panel31, 205);
    lv_obj_set_height(ui_Panel31, 76);
    lv_obj_set_align(ui_Panel31, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Panel31, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Panel31, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Panel31, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel31, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Panel31, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Panel31, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Panel31, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Panel31, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Panel31, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Image14 = lv_img_create(ui_Panel31);
    lv_img_set_src(ui_Image14, &ui_img_news_image_png);
    lv_obj_set_width(ui_Image14, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Image14, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Image14, 0);
    lv_obj_set_y(ui_Image14, -76);
    lv_obj_set_align(ui_Image14, LV_ALIGN_TOP_MID);
    lv_obj_add_flag(ui_Image14, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image14, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label40 = lv_label_create(ui_Panel29);
    lv_obj_set_width(ui_Label40, 280);
    lv_obj_set_height(ui_Label40, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label40, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label40,
                      "LVGL has launched a refreshed website featuring a colorful and modern logo. The update reflects the library's growth and commitment to providing cutting-edge graphical solutions for embedded systems. The new design enhances usability and showcases LVGL's robust capabilities.\n-----------------------------\nhttps://lvgl.io");
    lv_obj_set_style_text_font(ui_Label40, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Panel32 = lv_obj_create(ui_settingsMainPanel1);
    lv_obj_set_width(ui_Panel32, 280);
    lv_obj_set_height(ui_Panel32, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_align(ui_Panel32, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_Panel32, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_Panel32, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Panel32, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Panel32, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Panel32, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel32, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Panel32, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Panel32, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Panel32, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_Panel32, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Panel32, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Panel32, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Panel32, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Panel32, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label43 = lv_label_create(ui_Panel32);
    lv_obj_set_width(ui_Label43, 280);
    lv_obj_set_height(ui_Label43, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label43, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label43, "Yusuf Dikec's Casual Look Wins Silver at Paris Olympics");
    lv_obj_set_style_text_font(ui_Label43, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Panel33 = lv_obj_create(ui_Panel32);
    lv_obj_set_width(ui_Panel33, 205);
    lv_obj_set_height(ui_Panel33, 76);
    lv_obj_set_align(ui_Panel33, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Panel33, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Panel33, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Panel33, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel33, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Panel33, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Panel33, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Panel33, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Panel33, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Panel33, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Image15 = lv_img_create(ui_Panel33);
    lv_img_set_src(ui_Image15, &ui_img_news_image_png);
    lv_obj_set_width(ui_Image15, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Image15, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Image15, 0);
    lv_obj_set_y(ui_Image15, -152);
    lv_obj_set_align(ui_Image15, LV_ALIGN_TOP_MID);
    lv_obj_add_flag(ui_Image15, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image15, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label44 = lv_label_create(ui_Panel32);
    lv_obj_set_width(ui_Label44, 280);
    lv_obj_set_height(ui_Label44, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label44, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label44,
                      "Turkish shooter Yusuf Dikec made headlines at the Paris Olympics not just for his silver medal performance, but also for his casual, no-gear look. Dikec's relaxed style and exceptional skill have inspired many and highlighted the sport's accessibility.\n-----------------------------\nParis Olympics");
    lv_obj_set_style_text_font(ui_Label44, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Panel34 = lv_obj_create(ui_settingsMainPanel1);
    lv_obj_set_width(ui_Panel34, 280);
    lv_obj_set_height(ui_Panel34, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_align(ui_Panel34, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_Panel34, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_Panel34, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Panel34, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Panel34, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Panel34, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel34, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Panel34, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Panel34, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Panel34, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_Panel34, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Panel34, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Panel34, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Panel34, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Panel34, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label45 = lv_label_create(ui_Panel34);
    lv_obj_set_width(ui_Label45, 280);
    lv_obj_set_height(ui_Label45, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label45, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label45, "Chronos App Surpasses 50K Downloads on Google Play");
    lv_obj_set_style_text_font(ui_Label45, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Panel35 = lv_obj_create(ui_Panel34);
    lv_obj_set_width(ui_Panel35, 205);
    lv_obj_set_height(ui_Panel35, 76);
    lv_obj_set_align(ui_Panel35, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Panel35, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Panel35, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Panel35, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel35, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Panel35, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Panel35, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Panel35, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Panel35, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Panel35, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Image16 = lv_img_create(ui_Panel35);
    lv_img_set_src(ui_Image16, &ui_img_news_image_png);
    lv_obj_set_width(ui_Image16, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Image16, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Image16, 0);
    lv_obj_set_y(ui_Image16, -228);
    lv_obj_set_align(ui_Image16, LV_ALIGN_TOP_MID);
    lv_obj_add_flag(ui_Image16, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image16, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label46 = lv_label_create(ui_Panel34);
    lv_obj_set_width(ui_Label46, 280);
    lv_obj_set_height(ui_Label46, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label46, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label46,
                      "The Chronos app has reached an impressive milestone with over\n50,000 downloads on Google Play. The app's popularity continues to grow as it offers users innovative time-tracking and productivity features, solidifying its place in the market.\n-----------------------------\nGoogle Play: Chronos");
    lv_obj_set_style_text_font(ui_Label46, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Panel17 = lv_obj_create(ui_settingsMainPanel1);
    lv_obj_set_width(ui_Panel17, 280);
    lv_obj_set_height(ui_Panel17, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_align(ui_Panel17, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_Panel17, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_Panel17, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Panel17, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Panel17, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Panel17, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel17, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Panel17, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Panel17, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Panel17, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_Panel17, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Panel17, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Panel17, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Panel17, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Panel17, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label19 = lv_label_create(ui_Panel17);
    lv_obj_set_width(ui_Label19, 280);
    lv_obj_set_height(ui_Label19, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label19, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label19, "ESP32 C3 Mini LVGL UI Project Now Supports Installable Watchfaces");
    lv_obj_set_style_text_font(ui_Label19, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Panel21 = lv_obj_create(ui_Panel17);
    lv_obj_set_width(ui_Panel21, 205);
    lv_obj_set_height(ui_Panel21, 76);
    lv_obj_set_align(ui_Panel21, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Panel21, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Panel21, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Panel21, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel21, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Panel21, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Panel21, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Panel21, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Panel21, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Panel21, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Image17 = lv_img_create(ui_Panel21);
    lv_img_set_src(ui_Image17, &ui_img_news_image_png);
    lv_obj_set_width(ui_Image17, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Image17, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Image17, 0);
    lv_obj_set_y(ui_Image17, -304);
    lv_obj_set_align(ui_Image17, LV_ALIGN_TOP_MID);
    lv_obj_add_flag(ui_Image17, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image17, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label21 = lv_label_create(ui_Panel17);
    lv_obj_set_width(ui_Label21, 280);
    lv_obj_set_height(ui_Label21, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label21, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label21,
                      "The ESP32 C3 Mini LVGL UI project has introduced a new feature allowing users to install custom watchfaces. This update enhances the personalization options for users, enabling them to tailor their smartwatch experience to their preferences.\n-----------------------------\nGithub: fbiego  esp32-c3-mini");
    lv_obj_set_style_text_font(ui_Label21, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Panel22 = lv_obj_create(ui_settingsMainPanel1);
    lv_obj_set_width(ui_Panel22, 280);
    lv_obj_set_height(ui_Panel22, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_align(ui_Panel22, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_Panel22, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_Panel22, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Panel22, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Panel22, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Panel22, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel22, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Panel22, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Panel22, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Panel22, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_Panel22, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Panel22, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Panel22, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Panel22, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Panel22, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label22 = lv_label_create(ui_Panel22);
    lv_obj_set_width(ui_Label22, 280);
    lv_obj_set_height(ui_Label22, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label22, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label22, "'Apple Explained' YouTube Channel Discusses Windows Phone Failure");
    lv_obj_set_style_text_font(ui_Label22, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Panel23 = lv_obj_create(ui_Panel22);
    lv_obj_set_width(ui_Panel23, 205);
    lv_obj_set_height(ui_Panel23, 76);
    lv_obj_set_align(ui_Panel23, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Panel23, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Panel23, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Panel23, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel23, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Panel23, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Panel23, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Panel23, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Panel23, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Panel23, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Image18 = lv_img_create(ui_Panel23);
    lv_img_set_src(ui_Image18, &ui_img_news_image_png);
    lv_obj_set_width(ui_Image18, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Image18, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Image18, 0);
    lv_obj_set_y(ui_Image18, -380);
    lv_obj_set_align(ui_Image18, LV_ALIGN_TOP_MID);
    lv_obj_add_flag(ui_Image18, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image18, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label47 = lv_label_create(ui_Panel22);
    lv_obj_set_width(ui_Label47, 280);
    lv_obj_set_height(ui_Label47, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label47, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label47,
                      "The popular YouTube channel 'Apple Explained' dives into the reasons behind the failure of Windows Phone in their latest video. The detailed analysis explores the strategic missteps and market challenges that led to the platform's decline, providing viewers with an insightful look at one of tech's most intriguing stories.\n-----------------------------\nYoutube: Apple Explained");
    lv_obj_set_style_text_font(ui_Label47, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_appTitleIcon1, ui_event_appTitleIcon1, LV_EVENT_ALL, NULL);

}
