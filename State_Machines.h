/*
 * State_Machine_1.h
 *
 *  Created on: Apr 3, 2020
 *      Author: Katherine
 */

#ifndef STATE_MACHINES_H_
#define STATE_MACHINES_H_

#include <stdint.h>

enum states{Read_XYZ_Acc, Process_Display, Wait_PollSlider, Sensor_Disconnect};
extern uint8_t machine;
extern uint8_t end_flag;

enum states State_Machine_1(enum states state);
enum states State_Machine_2(enum states state);


#endif /* STATE_MACHINES_H_ */
