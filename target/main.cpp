extern "C"
{
#include <msp430.h>
#include "hal/wdt.h"
#include "hal/io.h"
#include "hal/button.h"
#include "hal/lcd.h"
#include "hal/rtc.h"
#include "hal/beepled.h"
#include "hal/aux_timer.h"
#include "hal/compass.h"
#include "hal/aes/aes256.h"
#include "hal/lcd_segments.h"
#include "hal/hal.h"
#include "common/svc/svc.h"
}

import fw.event;
import fw.loop;

extern "C" void clk_init(void)
{
	CSCTL0 = CSKEY; // Enable writing to CS registers

	PCONF(J, 4, (FUNC1 | IN)); /* LFXT pin */
	PCONF(J, 5, (FUNC1 | IN)); /* LFXT pin */

	CSCTL4 |= HFXTOFF;					  /* turn off HFXT */
	CSCTL1 = DCORSEL | DCOFSEL_4;		  /* DCO: 16 Mhz */
	CSCTL3 = DIVA__1 | DIVS__4 | DIVM__2; // SMCLK = 16MHz/4=4MHz, MCLK=16MHz/2=8MHz
	while (SFRIFG1 & OFIFG)
	{
		CSCTL5 &= ~(HFXTOFFG | LFXTOFF);
		SFRIFG1 &= ~OFIFG;
	}

	CSCTL0_H = 0; // Disable writing to CS registers
}

// Link to userguide
// https://www.ti.com/lit/ug/slau367p/slau367p.pdf

extern "C" void alarmCallback(const bool state)
{
	queueEvent(state ? (const Event &)AlarmDownEvent() : (const Event &)AlarmUpEvent());
};

extern "C" void lightCallback(const bool state)
{
	queueEvent(state ? (const Event &)LightDownEvent() : (const Event &)LightUpEvent());
};

extern "C" void modeCallback(const bool state)
{
	queueEvent(state ? (const Event &)ModeDownEvent() : (const Event &)ModeUpEvent());
};

extern "C" void tickCallback()
{
	queueEvent(TickEvent());
};

extern "C" int main(void)
{
	PM5CTL0 &= ~LOCKLPM5;
	wdt_clear();
	clk_init();
	io_init();
	rtc_init();
	lcd_init();
	button_init();
	aux_timer_init();
	frameworkInit();

	// volatile uint16_t reset_reason = hal_debug_read(0);

	svc_init();

	__eint(); // Enable interrupts

	while (true)
	{
		LPM3;

		// P9OUT |= BIT5;
		hal_lcd_set_mode(HAL_LCD_MODE_BUFFERED);
		hal_lcd_seg_set(HAL_LCD_SEG_24H, 1);
		workQueue();
		hal_lcd_seg_set(HAL_LCD_SEG_24H, 1);
		hal_lcd_update();
		// P9OUT &= ~BIT5;
	}
}