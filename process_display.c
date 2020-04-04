/*
 * process_display.c
 *
 *  Created on: Apr 3, 2020
 *      Author: Katherine
 */

#include <stdio.h>
#include "process_display.h"
#include "mma8451.h"

uint8_t read_cnt;
int16_t avg[3];
int16_t min[3];
int16_t max[3];

void update_data(void){
	for(uint8_t i = 0; i < 3; i++){
		//update average
		if(read_cnt == 1){
			avg[i] = acc_xyz[i];
		}else{
			avg[i] = (avg[i]*(read_cnt - 1) + acc_xyz[i]) / read_cnt;
		}
		//update min
		if(read_cnt == 1){
			min[i] = acc_xyz[i];
		}else{
			if(acc_xyz[i] < min[i]){
				min[i] = acc_xyz[i];
			}
		}
		//update max
		if(read_cnt == 1){
			max[i] = acc_xyz[i];
		}else{
			if(acc_xyz[i] > max[i]){
				max[i] = acc_xyz[i];
			}
		}
	}
}

void display_data(void){
	//print
	printf("\nReading Number %d:\n", read_cnt);
	printf("Last:\t X:%d\t Y:%d\t Z:%d\n", acc_xyz[0], acc_xyz[1], acc_xyz[2]);
	printf("Avg:\t X:%d\t Y:%d\t Z:%d\n", avg[0], avg[1], avg[2]);
	printf("Low:\t X:%d\t Y:%d\t Z:%d\n", min[0], min[1], min[2]);
	printf("High:\t X:%d\t Y:%d\t Z:%d\n", max[0], max[1], max[2]);
}


