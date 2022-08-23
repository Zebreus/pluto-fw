//
// Created by lennart on 9/19/21.
//

#include "./entrypoint.h"
#define PRIV(a) ((priv_t *)((a)->priv))
#include "casio.hpp"
#include "framework/loop.hpp"
#include "framework/Event.hpp"

Casio casio;
extern "C"
{
    void entrypoint(svc_main_proc_event_t event)
    {
        if (event & SVC_MAIN_PROC_EVENT_TICK)
        {
            //casio.onTick();
            trigger(TickEvent());
        }

        if (event & SVC_MAIN_PROC_EVENT_KEY_ENTER_LONG)
        {
            trigger(AlarmUpEvent());
        }
        if (event & SVC_MAIN_PROC_EVENT_KEY_ENTER)
        {
            trigger(AlarmDownEvent());
        }
        if (event & SVC_MAIN_PROC_EVENT_KEY_UP_LONG)
        {
            trigger(LightUpEvent());
        }
        if (event & SVC_MAIN_PROC_EVENT_KEY_UP)
        {
            trigger(LightDownEvent());
        }
        if (event & SVC_MAIN_PROC_EVENT_KEY_DOWN_LONG)
        {
            trigger(ModeUpEvent());
        }
        if (event & SVC_MAIN_PROC_EVENT_KEY_DOWN)
        {
            trigger(ModeDownEvent());
        }

        //     auto str = new std::string();
        //     str->append("oo");
        // //    try{
        // //        //throw (int) 5;
        // //    }catch(int hey){
        // //        int N = hey+6;
        // //    }

        //     hal_lcd_clear();
        //     svc_lcd_puts(8, str->data());
        //     // svc_lcd_puts(8, sv.data());
        //     hal_lcd_seg_set(HAL_LCD_SEG_COLON, 1);
        //     hal_lcd_seg_set_blink(HAL_LCD_SEG_COLON, true);
        //     if(event) {
        //         stringThing.toggle();
        //     }
        //     else if(event & SVC_MAIN_PROC_EVENT_KEY_UP) {
        //         app_exit();
        //     }

        //     svc_lcd_puti(0, 2, 0);
        //     svc_lcd_puti(2, 2, 0);
        //     svc_lcd_puti(4, 2, 0);
        //     delete str;
        //delete num;
    }
}
