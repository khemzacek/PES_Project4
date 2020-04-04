/*
 * SysTick_timer.h
 *
 *  Created on: Apr 3, 2020
 *      Author: Katherine
 */

#ifndef SYSTICK_TIMER_H_
#define SYSTICK_TIMER_H_

extern uint8_t timeout;

void SysTick_init(void);
void SysTick_Handler();
void start_SysTick(void);
void stop_SysTick(void);

#endif /* SYSTICK_TIMER_H_ */
