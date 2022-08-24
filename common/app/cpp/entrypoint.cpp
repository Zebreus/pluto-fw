#include "./entrypoint.h"

import fw.event;
import fw.loop;

extern "C"
{
    void entrypoint(svc_main_proc_event_t event)
    {

        if (event & SVC_MAIN_PROC_EVENT_TICK)
        {
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
    }
}
