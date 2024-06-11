#include <msp430.h>
#include "rtc.h"
#include "common/svc/util.h"
#include "hal.h"
#include "platform.h"

static volatile hal_rtc_timedate_t timedate_l;

static int16_t SECTION_INFOMEM rtc_cal_save = 0;

void rtc_init(void)
{
	RTCCTL0_H = RTCKEY_H;		 // Enable writing control registers
	RTCCTL1 = RTCMODE;			 // Set to calendar mode
	RTCCTL0_L &= ~RTCRDYIE_L;	 // Disable ready interrupt
	RTCPS1CTL_H |= RT1PSHOLD_H;	 // Hold the prescaler
	RT1PS = 0;					 // Reset the prescaler
	RTCPS1CTL |= RT1IP_6;		 // Set the prescaler interval to sec/4
	RTCPS1CTL |= RT1PSIE;		 // Enable prescaler interrupt
	RTCPS1CTL_H &= ~RT1PSHOLD_H; // Start the prescaler
	RTCCTL0_H = 0;				 // Disable writing control registers

	// prescaler 5 = 2hz
	// prescaler 6 = 1hz
	// prescaler 7 = 0.5hz

	// RT1PS steps from 0 to 256.
	// Interrupts are triggered every 256/(2*hz) steps
	// First trigger is at stepsize/2 not at zero
	// rdy interrupts happen at 0 and 128

	// // Enable, BCD, int every minute
	// RTCSEC = 0x00;	  // Set Seconds
	// RTCMIN = 0x00;	  // Set Minutes
	// RTCHOUR = 0x08;	  // Set Hours
	// RTCDOW = 0x02;	  // Set DOW
	// RTCDAY = 0x23;	  // Set Day
	// RTCMON = 0x08;	  // Set Month
	// RTCYEAR = 0x2005; // Set Year

	// RTCCTL13 &= ~RTCHOLD; // Enable RTC
	// RTCCTL1 &= ~RTCHOLD;  // Enable RTC
	// RTCCTL3 &= ~RTCHOLD;  // Enable RTC
}

void hal_rtc_get(hal_rtc_timedate_t *result)
{
	*result = timedate_l; // Copy time
}

void hal_rtc_set_time(hal_rtc_timedate_t *time)
{
	RTCCTL0_H = RTCKEY_H; // Enable writing control registers
	RTCCTL1 |= RTCHOLD;	  // Stop rtc
	RTCHOUR = time->h;
	RTCMIN = time->m;
	RTCSEC = time->s;
	RTCCTL1 &= ~RTCHOLD; // Start rtc
	RTCCTL0_H = 0;		 // Disable writing control registers
}

/* calculate day of week with monday=0 */
static int wday(int year, int month, int day)
{
	int adjustment, mm, yy;

	adjustment = (14 - month) / 12;
	mm = month + 12 * adjustment - 2;
	yy = year - adjustment;
	return ((day + (13 * mm - 1) / 5 +
			 yy + yy / 4 - yy / 100 + yy / 400) +
			6) %
		   7;
}

void hal_rtc_set_date(hal_rtc_timedate_t *date)
{
	RTCCTL0_H = RTCKEY_H; // Enable writing control registers
	RTCCTL1 |= RTCHOLD;	  // Stop rtc
	RTCDAY = date->dom;
	RTCMON = date->month;
	RTCYEAR = date->year;
	RTCDOW = wday(date->year, date->month, date->dom);
	RTCCTL1 &= ~RTCHOLD; // Start rtc
	RTCCTL0_H = 0;		 // Disable writing control registers
}

void hal_rtc_cal_set(int16_t cal)
{
	// rtc_cal_save = cal;
	// RTCCTL0_H = RTCKEY_H; // Enable writing control registers
	// 	if (cal < 0)
	// 		RTCOCAL = (-1 * cal) & 0xff;
	// 	else
	// 		RTCOCAL = RTCOCALS | (cal & 0xff);
	// RTCCTL0_H = 0;		 // Disable writing control registers
}

int16_t hal_rtc_cal_get(void)
{
	// int16_t r = RTCOCAL & 0xff;
	// if (!(RTCOCAL & RTCOCALS))
	// {
	// 	r *= -1;
	// }
	// return r;
}

extern void tickCallback();

void __attribute__((interrupt((RTC_VECTOR)))) RTC_ISR(void)
{
	int16_t iv = RTCIV;
	volatile uint8_t s = RTCSEC;
	volatile uint8_t ctr = RT1PS;

	if (RTCCTL1 & RTCRDY)
	{
		timedate_l.h = RTCHOUR;
		timedate_l.m = RTCMIN;
		timedate_l.s = RTCSEC;

		timedate_l.dow = RTCDOW;
		timedate_l.dom = RTCDAY;
		timedate_l.month = RTCMON;
		timedate_l.year = RTCYEAR;

		tickCallback();
		LPM3_EXIT;
	}
}
