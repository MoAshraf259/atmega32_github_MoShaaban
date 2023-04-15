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
#include "LM35.h"

uint16_t application(void);

ADC_Config_t ADC1_Config;

void ADC1_Init(void){
	ADC1_Config.PowerSource=ADC_Power_AVCC;
	ADC1_Config.ReadFirst=ADC_FirstRead_ADCH;
	ADC1_Config.mode=ADC_Mode_Interrupt;
	ADC1_Config.prescaler=ADC_Prescaler_128;
	ADC1_Config.Resolution=ADC_Res_10BIT;
	ADC_Init(&ADC1_Config);
}

DIO_Handle_t DIO1_Handle;
void DIO1_Init(void)
{

	DIO1_Handle.pDIOx=DIOA;
	DIO1_Handle.DIO_Config.MODE=INPUT;
	DIO1_Handle.DIO_Config.PinNumber=BIT_NUM_0;

	DIO_Init(&DIO1_Handle);
}

int main()
{
	LCD_Init();
	DIO1_Init();
	ADC1_Init();
	uint16_t temp=0;
	//uint8_t reminders;
	//ADC_StartConversionAsync(ADC_ChannelNumber0);

	ADC_ApplicaionEventCallBack(&application);

	while(1)
	{
		temp=application();
		//DIO_WriteToPort(DIOD, temp);
		//reminders= (uint8_t)((temp>>8) & (0x3));
		//DIO_WriteToPort(DIOC, (reminders<<6));
		LCD_SendNumber(temp);
	}
}

uint16_t application(void)
{
	ADC_StartConversionSync(ADC_ChannelNumber0);
	return LM35_Read(&ADC1_Config);
}



