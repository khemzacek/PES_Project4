/*
 * State_Machine_1.c
 *
 *  Created on: Apr 3, 2020
 *      Author: Katherine
 */

#include <stdio.h>
#include "State_Machine_1.h"
#include "LED_control.h"
#include "mma8451.h"
#include "delay.h"
#include "process_display.h"
#include "SysTick_timer.h"
#include "slider_polling.h"

uint8_t machine = 1;
uint8_t end_flag = 0;

enum states State_Machine_1(enum states state)
{
	enum states next_state = Read_XYZ_Acc;
	static uint8_t timeout_cnt = 0;
	uint32_t slider = 0;

	switch(state){
	case Read_XYZ_Acc:
		if(read_full_xyz()){
			//complete
			read_cnt++;
			next_state = Process_Display;
		}else{
			//disconnect
			next_state = Sensor_Disconnect;
		}
		break;
	case Process_Display:
		update_data();
		display_data();
		//complete
		next_state = Wait_PollSlider;
		break;
	case Wait_PollSlider:
		start_SysTick();
		while(!timeout){
			Touch_Scan_LH();	//dummy read prevents duplicate data
			slider = Touch_Scan_LH();	//keep slider read value
			if(slider > 50){			//slider touched (untouched baseline <50)
				stop_SysTick();
				if(slider > 500){
					//Right Touch
					LED_off();
					end_flag = 1;
					printf("Right Touch\n");
				}else{
					//Left Touch
					read_cnt = 0;
					next_state = Read_XYZ_Acc;
					machine = 2;
					printf("Left Touch\n");
				}
				break;
			}
			Delay(100);
		}
		if(timeout){
			stop_SysTick();
			timeout_cnt++;
			if(timeout_cnt < 6){
				//Timeout(1-5)
				next_state = Read_XYZ_Acc;
			}else{
				//Timeout 6
				timeout_cnt = 0;
				read_cnt = 0;
				next_state = Read_XYZ_Acc;
				machine = 2;
			}
			timeout = 0;
		}
		break;
	case Sensor_Disconnect:
		LED_on(red);
		end_flag = 1;
		break;
	}

	return next_state;
}
