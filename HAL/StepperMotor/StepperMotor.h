/*
 * StepperMotor.h
 *
 *  Created on: Apr 3, 2023
 *      Author: moham
 */

#ifndef HAL_STEPPERMOTOR_STEPPERMOTOR_H_
#define HAL_STEPPERMOTOR_STEPPERMOTOR_H_
#include "atmega32.h"

#define STOP				0
#define ClockWise			1
#define CounterClockWise	2

#define Stepper_Port		DIOD

#define coil_1		0
#define coil_2		1
#define coil_3		2
#define coil_4		3


void StepperMotor_Init(void);
void StepperMotor_ControlRotation(uint8_t rotation_mode);
void StepperMotor_Angle(uint16_t angle,uint8_t direction);
#endif /* HAL_STEPPERMOTOR_STEPPERMOTOR_H_ */
