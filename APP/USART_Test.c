/*
 * USART_Test.c
 *
 *  Created on: Apr 10, 2023
 *      Author: moham
 */


#include "atmega32.h"
#include "LCD.h"

void Txapplication(void);
void Rxapplication(void);
void countingBytes(void);
USART_Config_t USART1_Config;

void USART_MainInit(void)
{
	USART1_Config.SyncAsync=USART_Async;
	USART1_Config.CharSize=USART_CharSize_8;
	USART1_Config.Polarity=USART_Polarity_Falling;
	USART1_Config.StopBits=USART_StopBits_1;
	USART1_Config.mode=USART_Mode_RxTx;
	USART1_Config.parity=USART_Parity_Off;
	USART1_Config.BaudRate=USART_Baudrate_9600;

	USART_Init(&USART1_Config);
}

DIO_Handle_t DIO1_Handle;




void DIO_MainInit(void)
{
	DIO1_Handle.pDIOx=DIOD;
	DIO1_Handle.DIO_Config.MODE=OUTPUT;
	DIO1_Handle.DIO_Config.PinNumber=BIT_NUM_4;

	DIO_Init(&DIO1_Handle);
}

uint8_t TxMsg[]="My name Mohamed";
uint8_t RxMsg[8];

uint8_t Notifcation[]="Bytes sent :";

int main(void)
{

	LCD_Init();

	USART_MainInit();

	USART_SendDataIT(TxMsg, sizeof(TxMsg), Txapplication);
	USART_RecieveDataIT(Rxapplication);

	while(1)
	{

	}

}

void Txapplication(void)
{
	static uint8_t counter=1;
	LCD_SendString(Notifcation);
	lcd_set_cursor(1, 13);
	LCD_SendNumber(counter);
	counter++;
}

void Rxapplication(void)
{
	static uint8_t i=0;
	static uint8_t line_detect=0;
	if(line_detect==16)
	{
		lcd_set_cursor(2, 1);
	}
	else if(line_detect==31)
	{
		clr_lcd();
		line_detect=0;
	}

	RxMsg[i]=USART->UDR;
	if(RxMsg[i]=='0')
	{
		clr_lcd();
		line_detect=0;
	}
	else{
	LCD_SendChar(RxMsg[i]);
	}
	i++;
	line_detect++;
}


