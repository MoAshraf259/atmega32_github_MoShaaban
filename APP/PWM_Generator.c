/*
 * Timer1_delay.c
 *
 *  Created on: Apr 9, 2023
 *      Author: moham
 */


#include <stdint.h>
#include <stdio.h>
#include "atmega32.h"

void application(void);

TIMER1_Config_t TIMER1_Config;
DIO_Handle_t DIO_Handle;

void TIMER1_MainConfig(void)
{
	TIMER1_Config.Mode=TIMER1_Mode_FastPWM_ICR;
	TIMER1_Config.FastPWM_Mode=TIMER1_FastPWM_NonInverted;
	TIMER1_Config.Channel=Channel_A;
	TIMER1_Config.Prescaler=TIMER1_Prescaler8;
	TIMER1_Config.InputCaptureValue=20000;

	TIMER1_Init(&TIMER1_Config);
}

void DIO_MainInit(void)
{
	DIO_Handle.pDIOx=DIOD;
	DIO_Handle.DIO_Config.MODE=OUTPUT;
	DIO_Handle.DIO_Config.PinNumber=BIT_NUM_5;

	DIO_Init(&DIO_Handle);

}
int main (void)
{
	TIMER1_MainConfig();
	DIO_MainInit();
	//DIO_WriteToPin(DIOD, 5, HIGH);
	TIMER1_SendPWM(100, 20);
while(1)
	{

	}
}

void application(void)
{
	DIO_TogglePin(DIOD,0);
}
