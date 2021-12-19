#include "app.h"

static void conf_exit(void) {
	PRIV(app_current)->st.item_current = 0;
	app_exit();
}

/* settings for keybeep ******************************************************/
static uint8_t keybeep_get(void *ud) {
	return svc_beep_key_get_enable();
}

static void keybeep_set(uint8_t choice, void *ud) {
	svc_beep_key_set_enable(choice);
}

static const svc_menu_item_choice_t menu_item_keybeep = {
	.type = SVC_MENU_ITEM_T_CHOICE,
	.text = " keb",
	.choice_pos = 4,
	.n_choices = 2,
	.choices = {
		"of",
		"on",
	},
	.handler_set = keybeep_set,
	.handler_get = keybeep_get
};


static int32_t keybeep_freq_get(void *ud) {
	return svc_beep_key_get_freq();
}

static void keybeep_freq_set(uint8_t dig, int8_t dir, void *user_data) {
	int16_t inc = dir*ipow(10, dig);
	int16_t va = svc_beep_key_get_freq();
	va = CLAMP(va+inc, 400, 9999);
	svc_beep_key_set_freq(va);
}

static const svc_menu_item_adj_t menu_item_keybeep_freq = {
	.type = SVC_MENU_ITEM_T_ADJ,
	.header = "kf",
	.text = " kef",
	.digits = 4,
	.handler_get = keybeep_freq_get,
	.handler_set = keybeep_freq_set
};


static int32_t keybeep_duration_get(void *ud) {
	return svc_beep_key_get_duration();
}

static void keybeep_duration_set(uint8_t dig, int8_t dir, void *user_data) {
	int16_t inc = dir*ipow(10, dig);
	int16_t va = svc_beep_key_get_duration();
	va = CLAMP(va+inc, 1, 50);
	svc_beep_key_set_duration(va);
}

static const svc_menu_item_adj_t menu_item_keybeep_duration = {
	.type = SVC_MENU_ITEM_T_ADJ,
	.header = "kd",
	.text = " ked",
	.digits = 2,
	.handler_get = keybeep_duration_get,
	.handler_set = keybeep_duration_set
};


/* general beep enable *******************************************************/
static uint8_t beep_enable_get(void *ud) {
	return hal_beep_get_enabled();
}

static void beep_enable_set(uint8_t choice, void *ud) {
	hal_beep_set_enabled(choice);
}

static const svc_menu_item_choice_t menu_item_beep_enable = {
	.type = SVC_MENU_ITEM_T_CHOICE,
	.text = " ben",
	.choice_pos = 4,
	.n_choices = 2,
	.choices = {
		"of",
		"on",
	},
	.handler_set = beep_enable_set,
	.handler_get = beep_enable_get
};

/* settings for lcd **********************************************************/
static uint8_t lcd_contrast = 15;

static int32_t lcd_contrast_get(void *ud) {
	return lcd_contrast;
}

static void lcd_contrast_set(uint8_t dig, int8_t dir, void *user_data) {
	int16_t inc = dir*ipow(10, dig);
	lcd_contrast = CLAMP(lcd_contrast+inc, 0, 15);
	hal_lcd_set_contrast(lcd_contrast);
}

static const svc_menu_item_adj_t menu_item_lcd_contrast = {
	.type = SVC_MENU_ITEM_T_ADJ,
	.header = "lc",
	.text = " con",
	.digits = 2,
	.handler_get = lcd_contrast_get,
	.handler_set = lcd_contrast_set
};

/* repetitions for alarms ****************************************************/
static int32_t alarm_repetitions_get(void *ud) {
	return svc_melody_alarm_repetitions_get();
}

static void alarm_repetitions_set(uint8_t dig, int8_t dir, void *user_data) {
	int16_t inc = dir*ipow(10, dig);
	int16_t va = svc_melody_alarm_repetitions_get();
	svc_melody_alarm_repetitions_set(CLAMP(va+inc, 0, 200));
}

static const svc_menu_item_adj_t menu_item_alarm_repetitions = {
	.type = SVC_MENU_ITEM_T_ADJ,
	.header = "ar",
	.text = "arep",
	.digits = 3,
	.handler_get = alarm_repetitions_get,
	.handler_set = alarm_repetitions_set
};


/* idle time in seconds before going back to display time ********************/
static int32_t time_to_return_home_get(void *ud) {
	return svc_menu_timetohome_get();
}

static void time_to_return_home_set(uint8_t dig, int8_t dir, void *user_data) {
	if(!svc_menu_timetohome_get()) {
		svc_menu_timetohome_set(svc_menu_timetohome_min_get());
	}
	else {
		int16_t inc = dir*ipow(10, dig);
		int16_t va = svc_menu_timetohome_get();
		svc_menu_timetohome_set(CLAMP(va+inc, svc_menu_timetohome_min_get()-1, 200));
	}
}

static const svc_menu_item_adj_t menu_item_time_to_return_home = {
	.type = SVC_MENU_ITEM_T_ADJ,
	.header = "th",
	.text = " t2ho",
	.digits = 3,
	.handler_get = time_to_return_home_get,
	.handler_set = time_to_return_home_set
};


/* debug view ****************************************************************/
static void debug_enter(void *ud) {
	app_set_view(app_current, 1);
}

static const svc_menu_item_text_t menu_item_debug = {
	.type = SVC_MENU_ITEM_T_TEXT,
	.text = "dbg",
	.handler = debug_enter
};


static const svc_menu_item_text_t *menu_items[] = {
	(void*)&menu_item_keybeep,
	(void*)&menu_item_keybeep_freq,
	(void*)&menu_item_keybeep_duration,
	(void*)&menu_item_beep_enable,
	(void*)&menu_item_lcd_contrast,
	(void*)&menu_item_alarm_repetitions,
	(void*)&menu_item_time_to_return_home,
	(void*)&menu_item_debug
};

static const svc_menu_t menu = {
	.n_items = ARRAY_SIZE(menu_items),
	.items = (void*)menu_items,
	.handler_exit = conf_exit,
	.header = "cf",
	.header_pos = 8
};

static void main(uint8_t view, const app_t *app, svc_main_proc_event_t event) {
	svc_menu_run(&menu, &(PRIV(app)->st), event);
}

static app_view_t views[] = {
	{
		.main = main
	},
	{
		.main = app_app_conf_debug_main,
	}
};

static priv_t priv = {0};

const app_t app_app_conf = {
	.n_views = 2,
	.priv = (app_priv_t*)(&priv),
	.views = views
};
