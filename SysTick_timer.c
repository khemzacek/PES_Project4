/*
 * SysTick_timer.c
 *
 *  Created on: Apr 3, 2020
 *      Author: Katherine
 *
 *      heavily referenced -> "Embedded Systems Fundamentals with Arm Cortex-M based Microcontrollers"
 *      	by Alexander Dean, Chapter 7, Section "Timer Peripherals: SysTick Timer"
 */

#include <MKL25Z4.h>

uint8_t timeout = 0;

void SysTick_init(void)
{
	SysTick->LOAD = (3000000*3);		//alt timer 3MHz/(1/3 Hz) -> 3 sec interrupts
	NVIC_SetPriority (SysTick_IRQn, 3);		// Set interrupt priority
	SysTick->VAL = 0;						// Force load of reload value
	SysTick->CTRL = SysTick_CTRL_TICKINT_Msk;	//Enable interrupt, alt. clock source
												//Wait to enable timer (until start function)
}

void SysTick_Handler()
{
	timeout = 1;	//set timeout flag
}

void start_SysTick(void)
{
	SysTick->VAL = 0;	// Force load of reload value (resets to beginning of 3 sec timer)
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;	// Set enable bit
}

void stop_SysTick(void)
{
	SysTick->CTRL &= ~(SysTick_CTRL_ENABLE_Msk);	// Clear enable bit
}
