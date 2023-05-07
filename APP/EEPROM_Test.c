/*
 * EEPROM_Test.c
 *
 *  Created on: May 7, 2023
 *      Author: moham
 */
#include "atmega32.h"
#include "LCD.h"
#include "EEPROM.h"
uint8_t Buffer;
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

	EEPROM_SendToData(52, 100, EEPROM_PAGE1);
	EEPROM_ReceiveFromData(&Buffer, 100, EEPROM_PAGE1);
	LCD_SendNumber(Buffer);

	lcd_set_cursor(2, 1);

	EEPROM_SendToData(3, 24, EEPROM_PAGE2);
	EEPROM_ReceiveFromData(&Buffer, 24, EEPROM_PAGE2);
	LCD_SendNumber(Buffer);
}
