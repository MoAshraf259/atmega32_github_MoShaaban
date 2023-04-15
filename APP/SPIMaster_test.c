/*
 * SPI_Test.c
 *
 *  Created on: Apr 11, 2023
 *      Author: Noursine Hafez
 */

#include "LCD.h"
#include "../MCAL/atmega32.h"

void application(void);

SPI_Config_t SPI1_Config;

void SPI_MainInit(void)
{
	SPI1_Config.SPI_Mode=SPI_MASTER;
	SPI1_Config.SPI_SyncAsync=SPI_Async;
	SPI1_Config.ClockPhase=SPI_CPHA_SETUP;
	SPI1_Config.ClockPolarity=SPI_CPOL_RISING;
	SPI1_Config.DataOrder=SPI_DATAORDER_MSB;
	SPI1_Config.Prescaler=SPI_Prescaler_128;

	SPI_Init(&SPI1_Config);
}

DIO_Handle_t DIO1_Handle;

void DIO_MainInit(void)
{
	DIO1_Handle.pDIOx=DIOB;
	DIO1_Handle.DIO_Config.MODE=OUTPUT;
	DIO1_Handle.DIO_Config.PinNumber=BIT_NUM_5;
	DIO_Init(&DIO1_Handle);

	DIO1_Handle.DIO_Config.PinNumber=BIT_NUM_7;
	DIO_Init(&DIO1_Handle);

	DIO1_Handle.DIO_Config.PinNumber=BIT_NUM_4;
	DIO_Init(&DIO1_Handle);

	DIO1_Handle.DIO_Config.MODE=INPUT;
	DIO1_Handle.DIO_Config.PinNumber=BIT_NUM_6;
	DIO_Init(&DIO1_Handle);

}

uint8_t arr[]="MOHAMED ASHRAF";
uint8_t temp[]="Byte sent";

int main(void)
{

	SPI_MainInit();
	DIO_MainInit();
	LCD_Init();


	SPI_SendIT(arr , application,sizeof(arr));

	while (1)
	{

	}

}

void application(void)
{
	static uint8_t counter=1;
	lcd_set_cursor(1, 1);
	LCD_SendString(temp);
	lcd_set_cursor(1, 11);
	LCD_SendNumber(counter);
	counter++;
}
