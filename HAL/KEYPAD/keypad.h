/*
 * keypad.h
 *
 *  Created on: Mar 31, 2023
 *      Author: moham
 */

#ifndef HAL_KEYPAD_KEYPAD_H_
#define HAL_KEYPAD_KEYPAD_H_

#include "atmega32.h"

#define KPD_VALUES  {{'7', '8' , '9' , '/'}\
					,{'4', '5' , '6' , '*'}\
					,{'1', '2' , '3' , '-'}\
					,{'k', '0' , '=' , '+'}}


#define KEYPAD_PORT		DIOB

#define KEYPAD_R0		BIT_NUM_0
#define KEYPAD_R1		BIT_NUM_1
#define KEYPAD_R2		BIT_NUM_2
#define KEYPAD_R3		BIT_NUM_3

#define KEYPAD_C0		BIT_NUM_4
#define KEYPAD_C1		BIT_NUM_5
#define KEYPAD_C2		BIT_NUM_6
#define KEYPAD_C3		BIT_NUM_7

void Keypad_Init(void);

uint8_t Keypad_GetPressed(void);

#endif /* HAL_KEYPAD_KEYPAD_H_ */
