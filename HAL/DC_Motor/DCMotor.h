/*
 * DCMotor.h
 *
 *  Created on: Apr 3, 2023
 *      Author: moham
 */

#ifndef HAL_DC_MOTOR_DCMOTOR_H_
#define HAL_DC_MOTOR_DCMOTOR_H_
#include "atmega32.h"


#define DC_Port			DIOB

#define DC_MotorPin1	BIT_NUM_0
#define DC_MotorPin2	BIT_NUM_1

#define DC_ClockWise		0
#define DC_CounterClockWise	1
#define STOP				2

void DCMotor_Init(void);
void DCMotor_Rotate(uint8_t direction);


#endif /* HAL_DC_MOTOR_DCMOTOR_H_ */
