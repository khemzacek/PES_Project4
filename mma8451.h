/*
 * mma8451.h
 *
 *  Created on: Mar 29, 2020
 *      Author: Katherine
 *
 *      https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_8/I2C-Demo/inc/mma8451.h
 */

#ifndef MMA8451_H_
#define MMA8451_H_

#include <stdint.h>

#define MMA_ADDR 0x3A

#define REG_XHI 0x01
#define REG_XLO 0x02
#define REG_YHI 0x03
#define REG_YLO 0x04
#define REG_ZHI	0x05
#define REG_ZLO 0x06

#define REG_WHOAMI 0x0D
#define REG_CTRL1  0x2A
#define REG_CTRL4  0x2D

#define WHOAMI 0x1A

#define COUNTS_PER_G (4096.0)
#define M_PI (3.14159265)

uint8_t init_mma(void);
uint8_t read_full_xyz(void);
void read_xyz(void);
void convert_xyz_to_roll_pitch(void);

extern float roll, pitch;
extern int16_t acc_xyz[3];

#endif /* MMA8451_H_ */
