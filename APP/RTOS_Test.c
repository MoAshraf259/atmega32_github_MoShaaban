/*
 * RTOS_Test.c
 *
 *  Created on: Apr 18, 2023
 *      Author: moham
 */


#include "atmega32.h"

void LED1(void);
void LED2(void);
void LED3(void);

DIO_Handle_t DIO1_Handle;

void DIO1_MainInit(void)
{
	DIO1_Handle.pDIOx=DIOA;
	DIO1_Handle.DIO_Config.MODE=OUTPUT;

	DIO1_Handle.DIO_Config.PinNumber=BIT_NUM_0;
	DIO_Init(&DIO1_Handle);

	DIO1_Handle.DIO_Config.PinNumber=BIT_NUM_1;
	DIO_Init(&DIO1_Handle);

	DIO1_Handle.DIO_Config.PinNumber=BIT_NUM_2;
	DIO_Init(&DIO1_Handle);
}

int main (void)
{
	DIO1_MainInit();

	DIO_WriteToPin(DIOA, 0, LOW);
	DIO_WriteToPin(DIOA, 1, LOW);
	DIO_WriteToPin(DIOA, 2, LOW);

	RTOS_CreateTask(1000, 0, 1 , LED1);
	RTOS_CreateTask(2000, 1, 1 , LED2);
	RTOS_CreateTask(4000, 2, 1 , LED3);

	Rtos_RunRtos();


	while(1)
	{

	}
}

void LED1(void)
{
	DIO_TogglePin(DIOA, 0);
}

void LED2(void)
{
	DIO_TogglePin(DIOA, 1);
}

void LED3(void)
{
	DIO_TogglePin(DIOA, 2);
}
