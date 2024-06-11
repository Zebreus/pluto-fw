#pragma once

#ifdef __cplusplus

#include <array>
#include <string>
#include <stdlib.h>
//#include <new>
extern "C"
{
#endif
#include "common/svc/svc.h"
#include "hal.h"
#include "lcd_segments.h"

    void entrypoint(svc_main_proc_event_t event);

#ifdef __cplusplus
}
#endif