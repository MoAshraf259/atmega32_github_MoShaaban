/*
 * SPI_Test.c
 *
 *  Created on: Apr 12, 2023
 *      Author: moham
 */
#include "atmega32.h"
#include "LCD.h"


#define EEPROM_ADDRESS	(0b1010100)

void application (void);

uint8_t address=0x50;
uint8_t data[5];
uint8_t arr[2]={100,222};
uint8_t msg3[]="SEND DONE";
uint8_t arr1=100;
I2C_Handle_t I2C_Handle;

void I2C_MainInit(void)
{
	I2C_Handle.pI2C_Config.I2C_Mode=I2C_Mode_Sync;
	I2C_Handle.pI2C_Config.I2C_Ack=I2C_Ack_Enable;
	I2C_Handle.pI2C_Config.GenralCall_Status=I2C_GeneralCall_Enable;
	I2C_Handle.pI2C_Config.I2C_Prescaler=I2C_SCL_SPEED200K;
	I2C_Handle.pI2C_Config.I2C_Address=0x68;

	I2C_Init(&I2C_Handle);
}

int main(void)
{
	I2C_MainInit();

	I2C_MasterSendData(arr, sizeof(arr), EEPROM_ADDRESS);

	lcd_set_cursor(2, 1);

	_delay_ms(10);
	I2C_MasterSendData(&arr1, 1, EEPROM_ADDRESS);

	I2C_MasterRecieveData(data,	1, EEPROM_ADDRESS);

	LCD_SendNumber(data[0]);

	//I2C_Handle.TxRxState=4;
	//while (I2C_MasterSendDataIT(&I2C_Handle, arr, sizeof(arr), EEPROM_ADDRESS)!=I2C_Ready);
	//LCD_SendString(msg3);


	//I2C_Handle.TxRxState=4;

	//lcd_set_cursor(2, 1);

	//while(I2C_MasterRecieveDataIT(&I2C_Handle, data, 1, EEPROM_ADDRESS) != I2C_Ready);

	//LCD_SendNumber(data[0]);
	while(1)
	{

	}
}

void __vector_19(void) __attribute__((signal));
void __vector_19(void)
{

	I2C_ISRHandler(&I2C_Handle);
}

void application (void)
{

}
