/*
 * State_Machine_1.h
 *
 *  Created on: Apr 3, 2020
 *      Author: Katherine
 */

#ifndef STATE_MACHINE_1_H_
#define STATE_MACHINE_1_H_

#include <stdint.h>

enum states{Read_XYZ_Acc, Process_Display, Wait_PollSlider, Sensor_Disconnect};
extern uint8_t machine;
extern uint8_t end_flag;

enum states State_Machine_1(enum states state);


#endif /* STATE_MACHINE_1_H_ */
