/*
 * PWM_TIMER0test.c
 *
 *  Created on: Apr 6, 2023
 *      Author: moham
 */



#include <stdint.h>
#include <stdio.h>
#include "atmega32.h"
#include "LED.h"
#include "LCD.h"
#include "keypad.h"

void application(void);


TIMER0_Config_t TIMER0_Conf;

void TIMER0_MAININIT(void)
{
	TIMER0_Conf.CompareMatchValue=64;
	TIMER0_Conf.CompareMode_PhaseCorrect=TIMER0_PhaseCorrect_SetDown;
	TIMER0_Conf.Timer_Prescaler=TIMER0_Prescaler8;
	TIMER0_Conf.Waveform=TIMER0_Waveform_PhaseCorrect;

	TIMER0_Init(&application, &TIMER0_Conf);
}



DIO_Handle_t DIO1_Handle;
void DIO1_Init(void)
{
	DIO1_Handle.pDIOx=DIOB;
	DIO1_Handle.DIO_Config.MODE=OUTPUT;
	DIO1_Handle.DIO_Config.PinNumber=BIT_NUM_3;

	DIO_Init(&DIO1_Handle);
}

int main()
{

	DIO1_Init();
	TIMER0_MAININIT();

	while(1)
	{

	}
}

void application(void)
{
	static uint8_t counter=0;

	if(counter ==2 )
	{
		DIO_WriteToPin(DIOA, BIT_NUM_0, HIGH);
	}
	else if(counter==10)
	{
		DIO_WriteToPin(DIOA, BIT_NUM_0, LOW);
		counter=0;
	}
	counter++;
}
