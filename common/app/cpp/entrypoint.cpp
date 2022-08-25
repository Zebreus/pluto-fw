#include "./entrypoint.h"

import fw.event;
import fw.loop;

extern "C"
{
    void entrypoint(svc_main_proc_event_t event)
    {

        if (event & SVC_MAIN_PROC_EVENT_TICK)
        {
            queueEvent(TickEvent());
        }

        if (event & SVC_MAIN_PROC_EVENT_KEY_ENTER_LONG)
        {
            queueEvent(AlarmUpEvent());
        }
        if (event & SVC_MAIN_PROC_EVENT_KEY_ENTER)
        {
            queueEvent(AlarmDownEvent());
        }
        if (event & SVC_MAIN_PROC_EVENT_KEY_UP_LONG)
        {
            queueEvent(LightUpEvent());
        }
        if (event & SVC_MAIN_PROC_EVENT_KEY_UP)
        {
            queueEvent(LightDownEvent());
        }
        if (event & SVC_MAIN_PROC_EVENT_KEY_DOWN_LONG)
        {
            queueEvent(ModeUpEvent());
        }
        if (event & SVC_MAIN_PROC_EVENT_KEY_DOWN)
        {
            queueEvent(ModeDownEvent());
        }

        workQueue();
    }
}
