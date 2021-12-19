#include "common/app/app.h"
#include "common/app/apps.h"
#include "common/svc/svc.h"
#include "common/hal/hal.h"
#include "common/hal/lcd_segments.h"

typedef struct {
	APP_PRIV_COMMON
	svc_menu_state_t st;
} priv_t;

#define PRIV(a) ((priv_t*)((a)->priv))

static void launch(void *papp) {
	app_t *app = papp;
	app_launch(app);
}

static void menu_time(void)
{
	launch((void *)&app_app_time);
}

static const svc_menu_item_text_t menu_item0 = {
	.text = " time",
	.handler = launch,
	.user_data = (void *)&app_app_time,
};
// static const svc_menu_item_text_t menu_item2 = {
// 	.text = " alarm",
// 	.handler = launch,
// 	.user_data = (void *)&app_app_alarm,
// };
// static const svc_menu_item_text_t menu_item3 = {
// 	.text = "chro",
// 	.handler = launch,
// 	.user_data = (void *)&app_app_chro,
// };
// static const svc_menu_item_text_t menu_item4 = {
// 	.text = " play",
// 	.handler = launch,
// 	.user_data = (void *)&app_app_play,
// };
// static const svc_menu_item_text_t menu_item5 = {
// 	.text = " compa",
// 	.handler = launch,
// 	.user_data = (void *)&app_app_compass,
// };
// static const svc_menu_item_text_t menu_item6 = {
// 	.text = "speed",
// 	.handler = launch,
// 	.user_data = (void *)&app_app_speed,
// };
// static const svc_menu_item_text_t menu_item7 = {
// 	.text = "conf",
// 	.handler = launch,
// 	.user_data = (void *)&app_app_conf,
// };
// static const svc_menu_item_text_t menu_item8 = {
// 	.text = "   otp",
// 	.handler = launch,
// 	.user_data = (void *)&app_app_otp,
// };
// static const svc_menu_item_text_t menu_item9 = {
//         .text = "cool",
//         .handler = launch,
//         .user_data = (void *)&app_app_cool,
// };
static const svc_menu_item_text_t menu_item10 = {
        .text = "cpp",
        .handler = launch,
        .user_data = (void *)&app_app_cpp,
};

static const svc_menu_item_text_t *menu_items[] = {
	(void*)&menu_item0,
	// (void*)&menu_item1,
	// (void*)&menu_item2,
	// (void*)&menu_item3,
	// (void*)&menu_item4,
	// (void*)&menu_item5,
	// (void*)&menu_item6,
	// (void*)&menu_item7,
	// (void*)&menu_item8,
    // (void*)&menu_item9,
    (void*)&menu_item10,
};

static const svc_menu_t menu = {
	.n_items = ARRAY_SIZE(menu_items),
	.items = (void*)menu_items,
	.handler_exit = menu_time,
	.header = "la",
	.header_pos = 8
};


static void main(uint8_t view, const app_t *app, svc_main_proc_event_t event) {
	svc_menu_run(&menu, &(PRIV(app)->st), event);
}

static app_view_t view = {
	.main = main
};

static priv_t priv = {0};

const app_t app_app_launcher = {
	.n_views = 1,
	.priv = (app_priv_t*)(&priv),
	.views = &view
};
