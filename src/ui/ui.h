// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.1
// LVGL version: 8.3.11
// Project name: W10M

#ifndef _W10M_UI_H
#define _W10M_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

#include "ui_helpers.h"
#include "ui_events.h"

void closeNotificationPanel_Animation(lv_obj_t * TargetObject, int delay);
void openNotificationPanel_Animation(lv_obj_t * TargetObject, int delay);
void liveTileVertical6_Animation(lv_obj_t * TargetObject, int delay);
void liveTileHorizontal5_Animation(lv_obj_t * TargetObject, int delay);
// SCREEN: ui_homeScreen
void ui_homeScreen_screen_init(void);
extern lv_obj_t * ui_homeScreen;
extern lv_obj_t * ui_homePanel;
extern lv_obj_t * ui_startPanel;
extern lv_obj_t * ui_Panel7;
extern lv_obj_t * ui_Label7;
extern lv_obj_t * ui_Panel4;
extern lv_obj_t * ui_Label6;
extern lv_obj_t * ui_Panel13;
extern lv_obj_t * ui_Label15;
extern lv_obj_t * ui_Panel5;
extern lv_obj_t * ui_Label8;
void ui_event_Panel6(lv_event_t * e);
extern lv_obj_t * ui_Panel6;
extern lv_obj_t * ui_Label9;
extern lv_obj_t * ui_Panel8;
extern lv_obj_t * ui_Label10;
void ui_event_Panel12(lv_event_t * e);
extern lv_obj_t * ui_Panel12;
extern lv_obj_t * ui_Label14;
extern lv_obj_t * ui_tipsLiveImage;
void ui_event_Panel11(lv_event_t * e);
extern lv_obj_t * ui_Panel11;
extern lv_obj_t * ui_Label13;
extern lv_obj_t * ui_newsLiveImage;
extern lv_obj_t * ui_Panel14;
extern lv_obj_t * ui_Label16;
extern lv_obj_t * ui_Panel10;
extern lv_obj_t * ui_Label12;
extern lv_obj_t * ui_photosLiveImage;
extern lv_obj_t * ui_Panel9;
extern lv_obj_t * ui_Label11;
void ui_event_Panel15(lv_event_t * e);
extern lv_obj_t * ui_Panel15;
extern lv_obj_t * ui_Label17;
extern lv_obj_t * ui_Panel16;
extern lv_obj_t * ui_Label18;
extern lv_obj_t * ui_allAppsPanel;
extern lv_obj_t * ui_allAppsLabel;
extern lv_obj_t * ui_allAppsIcon;
extern lv_obj_t * ui_appsListPanel;
extern lv_obj_t * ui_Panel3;
extern lv_obj_t * ui_Panel18;
extern lv_obj_t * ui_Label5;
extern lv_obj_t * ui_Panel19;
extern lv_obj_t * ui_Panel20;
extern lv_obj_t * ui_Label20;
extern lv_obj_t * ui_navPanel;
extern lv_obj_t * ui_navBack;
extern lv_obj_t * ui_navHome;
extern lv_obj_t * ui_navSearch;
void ui_event_lockScreenPanel(lv_event_t * e);
extern lv_obj_t * ui_lockScreenPanel;
extern lv_obj_t * ui_Label41;
extern lv_obj_t * ui_Label39;
void ui_event_notificationPanel(lv_event_t * e);
extern lv_obj_t * ui_notificationPanel;
extern lv_obj_t * ui_quickActionPanel;
extern lv_obj_t * ui_Button4;
extern lv_obj_t * ui_Image4;
extern lv_obj_t * ui_Label30;
extern lv_obj_t * ui_Button5;
extern lv_obj_t * ui_Image5;
extern lv_obj_t * ui_Label31;
extern lv_obj_t * ui_Button6;
extern lv_obj_t * ui_Image6;
extern lv_obj_t * ui_Label32;
extern lv_obj_t * ui_Button7;
extern lv_obj_t * ui_Image7;
extern lv_obj_t * ui_Label33;
extern lv_obj_t * ui_Button8;
extern lv_obj_t * ui_Image8;
extern lv_obj_t * ui_Label34;
extern lv_obj_t * ui_Button2;
extern lv_obj_t * ui_Image2;
extern lv_obj_t * ui_Label24;
extern lv_obj_t * ui_Button3;
extern lv_obj_t * ui_Image3;
extern lv_obj_t * ui_Label29;
extern lv_obj_t * ui_Button9;
extern lv_obj_t * ui_Image9;
extern lv_obj_t * ui_Label35;
extern lv_obj_t * ui_Button10;
extern lv_obj_t * ui_Image10;
extern lv_obj_t * ui_Label36;
extern lv_obj_t * ui_Button11;
extern lv_obj_t * ui_Image11;
extern lv_obj_t * ui_Label37;
extern lv_obj_t * ui_Panel30;
extern lv_obj_t * ui_Label38;
extern lv_obj_t * ui_statusPanel;
extern lv_obj_t * ui_statusPanelLeft;
extern lv_obj_t * ui_statusPanelCellular;
extern lv_obj_t * ui_statusPanelWifi;
extern lv_obj_t * ui_statusPanelBluetooth;
void ui_event_statusPanelRight(lv_event_t * e);
extern lv_obj_t * ui_statusPanelRight;
extern lv_obj_t * ui_statusPanelBattery;
extern lv_obj_t * ui_statusPanelTime;
// SCREEN: ui_settingsScreen
void ui_settingsScreen_screen_init(void);
extern lv_obj_t * ui_settingsScreen;
extern lv_obj_t * ui_appTitlePanel2;
extern lv_obj_t * ui_appTitleName2;
void ui_event_appTitleIcon2(lv_event_t * e);
extern lv_obj_t * ui_appTitleIcon2;
extern lv_obj_t * ui_settingsMainPanel;
extern lv_obj_t * ui_TextArea1;
extern lv_obj_t * ui_Panel2;
extern lv_obj_t * ui_Image1;
extern lv_obj_t * ui_Label3;
extern lv_obj_t * ui_Label4;
// SCREEN: ui_appScreen
void ui_appScreen_screen_init(void);
extern lv_obj_t * ui_appScreen;
extern lv_obj_t * ui_appTitlePanel;
extern lv_obj_t * ui_appTitleName;
void ui_event_appTitleIcon(lv_event_t * e);
extern lv_obj_t * ui_appTitleIcon;
extern lv_obj_t * ui_appMainPanel;
extern lv_obj_t * ui_Label23;
extern lv_obj_t * ui_genSwitchPanel;
void ui_event_genSwitch(lv_event_t * e);
extern lv_obj_t * ui_genSwitch;
extern lv_obj_t * ui_genSwitchText;
extern lv_obj_t * ui_Button1;
extern lv_obj_t * ui_Label25;
extern lv_obj_t * ui_Dropdown1;
extern lv_obj_t * ui_Label27;
extern lv_obj_t * ui_Slider1;
extern lv_obj_t * ui_Panel28;
extern lv_obj_t * ui_Panel27;
extern lv_obj_t * ui_Label28;
extern lv_obj_t * ui_Bar1;
// SCREEN: ui_newsScreen
void ui_newsScreen_screen_init(void);
extern lv_obj_t * ui_newsScreen;
extern lv_obj_t * ui_appTitlePanel1;
extern lv_obj_t * ui_appTitleName1;
void ui_event_appTitleIcon1(lv_event_t * e);
extern lv_obj_t * ui_appTitleIcon1;
extern lv_obj_t * ui_settingsMainPanel1;
extern lv_obj_t * ui_Panel25;
extern lv_obj_t * ui_Label2;
extern lv_obj_t * ui_Panel1;
extern lv_obj_t * ui_Image13;
extern lv_obj_t * ui_Label42;
extern lv_obj_t * ui_Panel29;
extern lv_obj_t * ui_Label1;
extern lv_obj_t * ui_Panel31;
extern lv_obj_t * ui_Image14;
extern lv_obj_t * ui_Label40;
extern lv_obj_t * ui_Panel32;
extern lv_obj_t * ui_Label43;
extern lv_obj_t * ui_Panel33;
extern lv_obj_t * ui_Image15;
extern lv_obj_t * ui_Label44;
extern lv_obj_t * ui_Panel34;
extern lv_obj_t * ui_Label45;
extern lv_obj_t * ui_Panel35;
extern lv_obj_t * ui_Image16;
extern lv_obj_t * ui_Label46;
extern lv_obj_t * ui_Panel17;
extern lv_obj_t * ui_Label19;
extern lv_obj_t * ui_Panel21;
extern lv_obj_t * ui_Image17;
extern lv_obj_t * ui_Label21;
extern lv_obj_t * ui_Panel22;
extern lv_obj_t * ui_Label22;
extern lv_obj_t * ui_Panel23;
extern lv_obj_t * ui_Image18;
extern lv_obj_t * ui_Label47;
void ui_event____initial_actions0(lv_event_t * e);
extern lv_obj_t * ui____initial_actions0;


LV_IMG_DECLARE(ui_img_img5_png);    // assets/img5.png
LV_IMG_DECLARE(ui_img_phone_ic_png);    // assets/phone_ic.png
LV_IMG_DECLARE(ui_img_people_ic_png);    // assets/people_ic.png
LV_IMG_DECLARE(ui_img_outlook_ic_png);    // assets/outlook_ic.png
LV_IMG_DECLARE(ui_img_message_ic_png);    // assets/message_ic.png
LV_IMG_DECLARE(ui_img_wp_settings_png);    // assets/wp_settings.png
LV_IMG_DECLARE(ui_img_groove_ic_png);    // assets/groove_ic.png
LV_IMG_DECLARE(ui_img_tips_ic_png);    // assets/tips_ic.png
LV_IMG_DECLARE(ui_img_embedded_tile_png);    // assets/embedded_tile.png
LV_IMG_DECLARE(ui_img_news_ic_png);    // assets/news_ic.png
LV_IMG_DECLARE(ui_img_news_tile_png);    // assets/news_tile.png
LV_IMG_DECLARE(ui_img_camera_ic_png);    // assets/camera_ic.png
LV_IMG_DECLARE(ui_img_photos_ic_png);    // assets/photos_ic.png
LV_IMG_DECLARE(ui_img_photo_tile_png);    // assets/photo_tile.png
LV_IMG_DECLARE(ui_img_weather_ic_png);    // assets/weather_ic.png
LV_IMG_DECLARE(ui_img_edge_ic_png);    // assets/edge_ic.png
LV_IMG_DECLARE(ui_img_microsoft_ic_png);    // assets/microsoft_ic.png
LV_IMG_DECLARE(ui_img_wp_next_png);    // assets/wp_next.png
LV_IMG_DECLARE(ui_img_file_ic_png);    // assets/file_ic.png
LV_IMG_DECLARE(ui_img_wp_back_png);    // assets/wp_back.png
LV_IMG_DECLARE(ui_img_windows_logo_png);    // assets/windows_logo.png
LV_IMG_DECLARE(ui_img_wp_search_png);    // assets/wp_search.png
LV_IMG_DECLARE(ui_img_img2_png);    // assets/img2.png
LV_IMG_DECLARE(ui_img_airplane_ic_png);    // assets/airplane_ic.png
LV_IMG_DECLARE(ui_img_cellular_ic_png);    // assets/cellular_ic.png
LV_IMG_DECLARE(ui_img_wifi_ic_png);    // assets/wifi_ic.png
LV_IMG_DECLARE(ui_img_bluetooth_ic_png);    // assets/bluetooth_ic.png
LV_IMG_DECLARE(ui_img_brightness_ic_png);    // assets/brightness_ic.png
LV_IMG_DECLARE(ui_img_battery_ic_png);    // assets/battery_ic.png
LV_IMG_DECLARE(ui_img_hotspot_ic_png);    // assets/hotspot_ic.png
LV_IMG_DECLARE(ui_img_settings_ic_png);    // assets/settings_ic.png
LV_IMG_DECLARE(ui_img_vpn_ic_png);    // assets/vpn_ic.png
LV_IMG_DECLARE(ui_img_location_ic_png);    // assets/location_ic.png
LV_IMG_DECLARE(ui_img_wp_system_png);    // assets/wp_system.png
LV_IMG_DECLARE(ui_img_news_image_png);    // assets/news_image.png
LV_IMG_DECLARE(ui_img_img0_png);    // assets/img0.png
LV_IMG_DECLARE(ui_img_img1_png);    // assets/img1.png
LV_IMG_DECLARE(ui_img_img3_png);    // assets/img3.png
LV_IMG_DECLARE(ui_img_img4_png);    // assets/img4.png
LV_IMG_DECLARE(ui_img_img6_png);    // assets/img6.png
LV_IMG_DECLARE(ui_img_img7_png);    // assets/img7.png
LV_IMG_DECLARE(ui_img_img8_png);    // assets/img8.png
LV_IMG_DECLARE(ui_img_img9_png);    // assets/img9.png






void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
