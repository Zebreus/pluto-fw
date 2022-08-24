#pragma once

#include <stdint.h>
#include <stdbool.h>

#define BTN_ALARM 1 << 2
#define BTN_MODE 1 << 1
#define BTN_LIGHT 1
#define BTN_ALL (BTN_ALARM | BTN_MODE | BTN_LIGHT)

extern void alarmCallback(const bool state);
extern void lightCallback(const bool state);
extern void modeCallback(const bool state);

void button_init(void);
bool get_button_light();
bool get_button_mode();
bool get_button_alarm();