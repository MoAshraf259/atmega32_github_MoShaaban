/*
 * Multiplexingmode.c
 *
 *  Created on: Apr 6, 2023
 *      Author: moham
 */


#include "atmega32.h"
#include "7SEGMENT.h"

void application(void);

DIO_Handle_t SSD_Handle;
TIMER0_Config_t TIMER0_Conf;

void TIMER0_MAININIT(void)
{
	TIMER0_Conf.CompareMatchValue=250;
	TIMER0_Conf.CompareMode_NonPWM=TIMER0_CTC_OC0Dis;
	TIMER0_Conf.InterruptMode=TIMER0_Interrupt_CTC;
	TIMER0_Conf.Timer_Prescaler=TIMER0_Prescaler8;
	TIMER0_Conf.Waveform=TIMER0_Waveform_CTC;
	TIMER0_Conf.mode=TIMER0_Mode_Interrupt;

	TIMER0_Init(&application, &TIMER0_Conf);
}




void SSD1_Init(void)
{
	SSD_Handle.pDIOx=DIOC;

	SSD_Handle.DIO_Config.MODE=OUTPUT;

	SSD_Init(&SSD_Handle);

	SSD_Handle.pDIOx=DIOD;
	SSD_Handle.DIO_Config.PinNumber=BIT_NUM_0;
	DIO_Init(&SSD_Handle);

	SSD_Handle.DIO_Config.PinNumber=BIT_NUM_1;
	DIO_Init(&SSD_Handle);


}
uint8_t y=9,x=0;
int main(void)
{
	SSD1_Init();
	TIMER0_MAININIT();
	DIO_WriteToPin(DIOD	, 0, LOW);
	DIO_WriteToPin(DIOD	, 1, HIGH);

	while(1)
	{
		if(y==0 && x==9)
		{
			y=9;
			x=0;
		}
		DIO_TogglePin(DIOD, 0);
		DIO_TogglePin(DIOD, 1);
		_delay_ms(10);
		SSDDispNum(DIOC, y);
		DIO_TogglePin(DIOD, 0);
		DIO_TogglePin(DIOD, 1);
		_delay_ms(10);
		SSDDispNum(DIOC, x);
	}
}

void application(void)
{
	static uint16_t counter=0;

	if(counter ==4000)
	{
		y--;
		x++;
		counter=0;
	}
	else
	{
		counter++;
	}

}
