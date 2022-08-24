#include <msp430.h>
#include <stdint.h>
#include <stdbool.h>
#include "button.h"
#include "io.h"

#define COUNTER_MAX 20
#define COUNTER_TRIGGER_HIGH 12
#define COUNTER_TRIGGER_LOW 8

#define DEB_RUNTIME 500 /* 5s */

volatile bool alarmDown;
volatile bool lightDown;
volatile bool modeDown;

volatile uint16_t debrun = 0;

void button_init(void)
{
	PCONF(9, 4, INPD); /* button alarm */
	PCONF(J, 0, INPD); /* button light */
	PCONF(J, 2, INPD); /* button mode */

	TA1CTL |= TASSEL__ACLK | TAIE;
	TA1CCR0 = 327; /* results in around 100Hz */

	TA3CTL |= TASSEL__ACLK | MC__UP | TAIE;
	TA3CCR0 = 2048; /* results in 16Hz */
}

void __attribute__((interrupt((TIMER3_A1_VECTOR)))) TimerA3_1_ISR(void)
{
	TA3CTL &= ~TAIFG;
	if (PGET(9, 4) | PGET(J, 2) | PGET(J, 0))
	{
		TA1CTL |= MC__UP;
		debrun = 0;
	}
}

void __attribute__((interrupt((TIMER1_A1_VECTOR)))) TimerA1_1_ISR(void)
{
	static uint8_t counterLight, counterAlarm, counterMode;
	TA1CTL &= ~TAIFG;

	volatile value = PGET(9, 4);
	volatile value2 = PGET(9, 3);
	volatile value3 = PGET(9, 5);
	volatile value4 = P9IN;
	bool alarmPressed = PGET(9, 4) != 0;
	bool lightPressed = PGET(J, 0) != 0;
	bool modePressed = PGET(J, 2) != 0;

	counterAlarm += alarmPressed
						? counterAlarm < COUNTER_MAX ? 1 : 0
					: counterAlarm > 0 ? -1
									   : 0;
	counterLight += lightPressed
						? counterLight < COUNTER_MAX ? 1 : 0
					: counterLight > 0 ? -1
									   : 0;
	counterMode += modePressed
					   ? counterMode < COUNTER_MAX ? 1 : 0
				   : counterMode > 0 ? -1
									 : 0;

	if (!alarmDown && counterAlarm >= COUNTER_TRIGGER_HIGH)
	{
		alarmDown = true;
	}
	if (alarmDown && counterAlarm <= COUNTER_TRIGGER_LOW)
	{
		alarmDown = false;
	}

	if (!lightDown && counterLight >= COUNTER_TRIGGER_HIGH)
	{
		lightDown = true;
	}
	if (lightDown && counterLight <= COUNTER_TRIGGER_LOW)
	{
		lightDown = false;
	}

	if (!modeDown && counterMode >= COUNTER_TRIGGER_HIGH)
	{
		modeDown = true;
	}
	if (modeDown && counterMode <= COUNTER_TRIGGER_LOW)
	{
		modeDown = false;
	}

	if (debrun < DEB_RUNTIME)
		debrun += 1;
	else
	{
		TA1CTL &= ~MC_3;
	}
	LPM3_EXIT;
}

bool get_button_alarm()
{
	bool value;
	__dint();
	__no_operation();
	value = alarmDown;
	__nop();
	__eint();
	return value;
}

bool get_button_light()
{
	bool value;
	__dint();
	__no_operation();
	value = lightDown;
	__nop();
	__eint();
	return value;
}

bool get_button_mode()
{
	bool value;
	__dint();
	__no_operation();
	value = modeDown;
	__nop();
	__eint();
	return value;
}