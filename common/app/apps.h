#pragma once
#include "app.h"

extern const app_t app_app_launcher;
extern const app_t app_app_time;
// extern const app_t app_app_conf;
// extern const app_t app_app_play;
// extern const app_t app_app_chro;
// extern const app_t app_app_alarm;
// extern const app_t app_app_compass;
// extern const app_t app_app_otp;
// extern const app_t app_app_speed;
// extern const app_t app_app_cool;
extern void coolfunction(uint8_t view, const app_t *app, svc_main_proc_event_t event);
