/*
 * Timer1_delay.c
 *
 *  Created on: Apr 9, 2023
 *      Author: moham
 */


#include <stdint.h>
#include <stdio.h>
#include "atmega32.h"


TIMER1_Config_t TIMER1_Config;
DIO_Handle_t DIO_Handle;

void TIMER1_MainConfig(void)
{
	TIMER1_Config.Mode=TIMER1_Mode_CTC;
	TIMER1_Config.CompareMode=TIMER1_NonPWM_Normal;
	TIMER1_Config.Prescaler=TIMER1_Prescaler1024;

	TIMER1_Init(&TIMER1_Config);
}

void DIO_MainInit(void)
{
	DIO_Handle.pDIOx=DIOD;
	DIO_Handle.DIO_Config.MODE=OUTPUT;
	DIO_Handle.DIO_Config.PinNumber=BIT_NUM_0;

	DIO_Init(&DIO_Handle);

}


int main (void)
{
	TIMER1_MainConfig();
	DIO_MainInit();

	DIO_WriteToPin(DIOD, 0, HIGH);
	TIMER1_DelaySync_ms(1000);
	DIO_WriteToPin(DIOD, 0, LOW);

	//Enable the WDT
	Watchdog_Enable();
	Watchdog_SetSleepTime(1);

	while(1)
	{

	}
}
