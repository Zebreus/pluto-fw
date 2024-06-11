#include <msp430.h>
#include "wdt.h"
#include "lcd_segments.h"

void wdt_clear(void)
{
	WDTCTL = WDTPW | WDTHOLD;
	// WDTCTL = WDT_ARST_1000;
}
