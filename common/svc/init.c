#include "init.h"
#include "hal.h"

void svc_init(void)
{
	hal_aes_init();
}
