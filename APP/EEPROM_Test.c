/*
 * EEPROM_Test.c
 *
 *  Created on: May 7, 2023
 *      Author: MohamedAshraf
 */
#include "atmega32.h"
#include "LCD.h"
#include "EEPROM.h"

uint8_t Buffer1,Buffer2;

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
	LCD_Init();

	I2C_MainInit();

	EEPROM_SendToData(44,50);
	EEPROM_SendToData(3,51);



	EEPROM_ReceiveFromData(&Buffer2, 51,1);
	EEPROM_ReceiveFromData(&Buffer1,50,1);

	LCD_SendNumber(Buffer1);

	lcd_set_cursor(2, 1);

	LCD_SendNumber(Buffer2);

}
