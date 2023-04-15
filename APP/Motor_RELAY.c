/*
 * main.c
 *
 *  Created on: Mar 21, 2023
 *      Author: Mohamed Ashraf
 */
/********************  Mohamed Ashraf Shaaban     *****************/



#include <stdint.h>
#include <stdio.h>
#include "atmega32.h"
#include <util/delay.h>
#include "LED.h"
#include "LCD.h"
#include "keypad.h"
#include "DCMotor.h"



EXTI_Config_t EXTI0_Config;

void EXTI_INT0_Init(void){
	EXTI0_Config.EXTI_Number=EXTI0;
	EXTI0_Config.InteruptMode=EXTI_FALLING_EDGE;

	EXTI_Init(&EXTI0_Config);
}

DIO_Handle_t DIO1_Handle;

void DIO1_Init(void)
{
	DIO1_Handle.pDIOx=DIOB;

	DIO1_Handle.DIO_Config.MODE=OUTPUT;

	DIO1_Handle.DIO_Config.PinNumber=BIT_NUM_0;
	DIO_Init(&DIO1_Handle);

	DIO1_Handle.DIO_Config.PinNumber=BIT_NUM_1;
	DIO_Init(&DIO1_Handle);
}

int main()
{
	 DIO1_Init();
	while(1)
	{


	}

}





