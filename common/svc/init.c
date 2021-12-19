#include "init.h"
#include "common/hal/hal.h"

void svc_init(void) {
	hal_aes_init();
}
