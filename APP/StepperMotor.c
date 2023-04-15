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
#include "StepperMotor.h"





DIO_Handle_t DIO1_Handle;

void DIO1_Init(void)
{
	DIO1_Handle.pDIOx=DIOD;

	DIO1_Handle.DIO_Config.MODE=OUTPUT;
	DIO1_Handle.DIO_Config.PinNumber=BIT_NUM_6;

	DIO_Init(&DIO1_Handle);
}

int main()
{
	StepperMotor_Init();
	StepperMotor_Angle(10,ClockWise);

	while(1)
	{

	}

}





