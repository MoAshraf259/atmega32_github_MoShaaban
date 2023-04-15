/*
 * SPI_Test.c
 *
 *  Created on: Apr 11, 2023
 *      Author: Mohamed Ashraf
 */

#include "atmega32.h"
#include "LCD.h"

void application(void);

SPI_Config_t SPI1_Config;

void SPI_MainInit(void)
{
	SPI1_Config.SPI_Mode=SPI_SLAVE;
	SPI1_Config.SPI_SyncAsync=SPI_Async;
	SPI1_Config.ClockPhase=SPI_CPHA_SETUP;
	SPI1_Config.ClockPolarity=SPI_CPOL_RISING;
	SPI1_Config.DataOrder=SPI_DATAORDER_MSB;


	SPI_Init(&SPI1_Config);
}

DIO_Handle_t DIO1_Handle;

void DIO_MainInit(void)
{
	DIO1_Handle.pDIOx=DIOB;
	DIO1_Handle.DIO_Config.MODE=INPUT;
	DIO1_Handle.DIO_Config.PinNumber=BIT_NUM_5;
	DIO_Init(&DIO1_Handle);

	DIO1_Handle.DIO_Config.PinNumber=BIT_NUM_7;
	DIO_Init(&DIO1_Handle);

	DIO1_Handle.DIO_Config.PinNumber=BIT_NUM_4;
	DIO_Init(&DIO1_Handle);

	DIO1_Handle.DIO_Config.MODE=OUTPUT;
	DIO1_Handle.DIO_Config.PinNumber=BIT_NUM_6;
	DIO_Init(&DIO1_Handle);

}

uint8_t arr=5;
uint8_t temp=0;


int main(void)
{

	SPI_MainInit();
	DIO_MainInit();
	LCD_Init();

	SPI_RecieveIT(application);
	while (1)
	{

	}

}

void application(void)
{
	uint8_t received =SPI->SPDR;
	LCD_SendChar(received);
}
