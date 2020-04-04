/*
 * process_display.h
 *
 *  Created on: Apr 3, 2020
 *      Author: Katherine
 */

#ifndef PROCESS_DISPLAY_H_
#define PROCESS_DISPLAY_H_

#include <stdint.h>

extern uint8_t read_cnt;
extern int16_t avg[3];
extern int16_t min[3];
extern int16_t max[3];

void update_data(void);
void display_data(void);

#endif /* PROCESS_DISPLAY_H_ */
