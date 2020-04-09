/*
 * State_Machine_1.c
 *
 *  Created on: Apr 3, 2020
 *      Author: Katherine
 */

#include <stdio.h>
#include <State_Machines.h>
#include "LED_control.h"
#include "mma8451.h"
#include "delay.h"
#include "process_display.h"
#include "SysTick_timer.h"
#include "slider_polling.h"

uint8_t machine = 1;
uint8_t end_flag = 0;
uint8_t timeout_cnt = 0;

enum states State_Machine_1(enum states state)
{
	enum states next_state = Read_XYZ_Acc;
	uint32_t slider = 0;

	switch(state){
	case Read_XYZ_Acc:
		printf("Read XYZ from Accelerometer\n");
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
		printf("Processing and Updating Data\n");
		update_data();
		display_data();
		//complete
		next_state = Wait_PollSlider;
		break;
	case Wait_PollSlider:
		printf("Waiting and Polling Slider\n");
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
			printf("Timeout number %d", timeout_cnt);
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
		printf("Sensor Disconnected\n");
		LED_on(red);
		end_flag = 1;
		break;
	}

	return next_state;
}


/* STATE MACHINE 2 */
enum events{complete, disconnect, timeout1_5, timeout6, Lslider, Rslider};

/* functions for state actions */
enum events Read_XYZ_Acc_fn(){
	printf("Reading XYZ from Accelerometer\n");
	if(read_full_xyz()){
		read_cnt++;
		return complete;
	}else{
		return disconnect;
	}
}

enum events Process_Display_fn(){
	printf("Processing and Displaying Data\n");
	update_data();
	display_data();
	return complete;
}

enum events Wait_PollSlider_fn(){
	printf("Waiting and Polling Slider\n");
	uint32_t slider = 0;
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
				return Rslider;
			}else{
				//Left Touch
				read_cnt = 0;
				machine = 1;
				printf("Left Touch\n");
				return Lslider;
			}
		}
		Delay(100);
	}
	stop_SysTick();
	timeout_cnt++;
	printf("Timeout Number %d", timeout_cnt);
	if(timeout_cnt < 6){
		//Timeout(1-5)
		timeout = 0;
		return timeout1_5;
	}else{
		//Timeout 6
		timeout_cnt = 0;
		read_cnt = 0;
		machine = 2;
		timeout = 0;
		return timeout6;
	}
}

enum events Sensor_Disconnect_fn(){
	printf("Sensor Disconnected\n");
	LED_on(red);
	end_flag = 1;
	return disconnect;
}


// Creating state table
struct sStateTableEntry{
	enum events (*action)(void);
	enum states eventNextState[6];
};

struct sStateTableEntry stateTable[4] = {
		{&Read_XYZ_Acc_fn, Process_Display, Sensor_Disconnect, Sensor_Disconnect, Sensor_Disconnect, Sensor_Disconnect, Sensor_Disconnect},
		{&Process_Display_fn, Wait_PollSlider, Sensor_Disconnect, Sensor_Disconnect, Sensor_Disconnect, Sensor_Disconnect, Sensor_Disconnect},
		{&Wait_PollSlider_fn, Sensor_Disconnect, Sensor_Disconnect, Read_XYZ_Acc, Read_XYZ_Acc, Read_XYZ_Acc, Sensor_Disconnect},
		{&Sensor_Disconnect_fn, Sensor_Disconnect, Sensor_Disconnect, Sensor_Disconnect, Sensor_Disconnect, Sensor_Disconnect, Sensor_Disconnect}
};

// Main state machine function
enum states State_Machine_2(enum states state){
	enum states next_state = Read_XYZ_Acc;
	enum events current_event;

	// call fn which performs actions for state
	// event outcome returned to current_event
	current_event = (*(stateTable[state].action))();

	// get next state from table based on current event and state
	next_state = stateTable[state].eventNextState[current_event];

	return next_state;
}
