/*
 * ICU_Timer1.c
 *
 *  Created on: Apr 10, 2023
 *      Author: moham
 */




#include <stdint.h>
#include <stdio.h>
#include "atmega32.h"
#include "LCD.h"
uint32_t data=0;
void application(void);

uint8_t arr1[]="OF Ticks :";
uint8_t arr2[]="CTC Ticks :";

TIMER1_Config_t TIMER1_Config;
DIO_Handle_t DIO_Handle;
TIMER0_Config_t TIMER0_Config;

void TIMER1_MainConfig(void)
{
	TIMER1_Config.Mode=TIMER1_Mode_Normal;
	TIMER1_Config.Prescaler=TIMER1_Prescaler1024;

	TIMER1_Init(&TIMER1_Config);
}

void TIMER0_MainConfig(void)
{
	TIMER0_Config.Waveform=TIMER0_Waveform_FastPWM;
	TIMER0_Config.CompareMode_FastPWM=TIMER0_FastPWM_NonInverting;
	TIMER0_Config.CompareMatchValue=254;
	TIMER0_Config.Timer_Prescaler=TIMER0_Prescaler1024;

	TIMER0_Init(&application, &TIMER0_Config);
}
void DIO_MainInit(void)
{
	DIO_Handle.pDIOx=DIOD;
	DIO_Handle.DIO_Config.MODE=OUTPUT;
	DIO_Handle.DIO_Config.PinNumber=BIT_NUM_5;

	DIO_Init(&DIO_Handle);

	DIO_Handle.pDIOx=DIOB;
	DIO_Handle.DIO_Config.PinNumber=BIT_NUM_3;
	DIO_Init(&DIO_Handle);

	DIO_Handle.pDIOx=DIOD;
	DIO_Handle.DIO_Config.PinNumber=BIT_NUM_6;
	DIO_Handle.DIO_Config.MODE=INPUT;
	DIO_Init(&DIO_Handle);
}





int main (void)
{
	LCD_Init();

	LCD_SendString(arr1);
	lcd_set_cursor(2, 1);
	LCD_SendString(arr2);

	TIMER1_MainConfig();
	TIMER1_EdgeDetectInput(InputCapture_Rising);
	TIMER1_CaptureInterrupt(&application);
	TIMER0_MainConfig();
while(1)
	{

	}
}

void application(void)
{
	static uint16_t ticks=0,compare=0;
	static uint8_t r1=0;
	r1++;
	if(r1==1)
	{
		ticks=TIMER1->ICR1;
		lcd_set_cursor(1, 11);
		LCD_SendNumber(ticks);
		TIMER1_CaptureInterrupt(&application);
		TIMER1_EdgeDetectInput(InputCapture_Falling);
	}
	else if(r1==2)
	{
		compare=TIMER1->ICR1;
		compare=compare-ticks;
		DisableGlobalInterrupt();
		lcd_set_cursor(2, 11);
		LCD_SendNumber(compare);

	}
}

