#include "svc.h"
#include "aux_timer.h"
#include "common/hal/hal.h"
#include "common/hal/lcd_segments.h"
#include "common/app/cpp/entrypoint.h"
#include <unistd.h>
#include <stdio.h>

void svc_main_proc(svc_main_proc_event_t event)
{
	static uint8_t keypress;
	if (event & (SVC_MAIN_PROC_EVENT_KEY_ANY | SVC_MAIN_PROC_EVENT_KEY_ANY_LONG))
	{
		keypress = 1;
	}
	// if(event & SVC_MAIN_PROC_EVENT_AUX_TIMER) {
	// 	svc_aux_timer_handler();
	// }
	if (event & SVC_MAIN_PROC_EVENT_TICK)
	{
		// static uint8_t div;
		// if(!div) { /* prescale to one second */
		// 	svc_seconds_since_last_set_process();
		// 	svc_menu_process_timetohome(keypress);
		// 	keypress = 0;
		// }
		// div = (div+1)%4;

		// svc_compass_process();
		// svc_lcd_blink_process();
		svc_rtc_adj_process();
	}
	if (!(event & SVC_MAIN_PROC_EVENT_AUX_TIMER) || svc_aux_timer_get_call_main())
	{
		hal_lcd_set_mode(HAL_LCD_MODE_BUFFERED);
		// if(app_view_changed) {
		// 	if(app_current->views[app_current->priv->view_current].enter) {
		// 		app_current->views[app_current->priv->view_current].enter(app_current->priv->view_current, app_current);
		// 		app_view_changed = 0;
		// 	}
		// }
		entrypoint(event);
	}

	// if(svc_rtc_adj_get_pending()) {
	// 	hal_lcd_seg_set(HAL_LCD_SEG_PM, 1);
	// 	hal_lcd_seg_set_blink(HAL_LCD_SEG_PM, 1);
	// }
	// else {
	// 	hal_lcd_seg_set(HAL_LCD_SEG_PM, 0);
	// }
}
