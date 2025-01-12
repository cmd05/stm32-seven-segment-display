/**
 * systick.c
 * 
 * Author: cmd05
 */

#include "stm32f4xx.h"

#define SYSTICK_LOAD_VAL		(16000)		// 16Mhz => 16000 cycles per ms
#define CTRL_ENABLE				(1U << 0)
#define CTRL_CLKSRC				(1U << 2) 	// internal clock source
#define CTRL_COUNTFLAG			(1U << 16)

void systickDelayMs(int delay) {
	SysTick->LOAD = SYSTICK_LOAD_VAL - 1; // STRVR register
	SysTick->VAL = 0; // clear STCVR register

	// enable systick and select internal clock source
	SysTick->CTRL = CTRL_ENABLE | CTRL_CLKSRC; // STCSR register

	// wait for required delay time
	for(int i = 0; i < delay; i++) {
		while((SysTick->CTRL & CTRL_COUNTFLAG) == 0)
			;
	}

	// disable SysTick
	SysTick->CTRL = 0;
}