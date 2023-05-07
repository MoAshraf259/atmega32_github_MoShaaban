/*
 * EEPROM.c
 *
 *  Created on: May 7, 2023
 *      Author: moham
 */
#include "EEPROM.h"

void EEPROM_SendToData(uint8_t data,uint8_t ByteNumber,uint8_t PageNumber)
{
	uint8_t arr[2]={ByteNumber,data};
	uint8_t address=EEPROM_ADDRESS | (PageNumber);

	I2C_MasterSendData(arr, sizeof(arr), address);
	_delay_ms(10);
}

void EEPROM_ReceiveFromData(uint8_t *data,uint8_t ByteNumber,uint8_t PageNumber)
{
	uint8_t address=EEPROM_ADDRESS | (PageNumber);
	I2C_MasterSendData(&ByteNumber, 1, address);
	I2C_MasterRecieveData(data, 1, address);
}

void EEPROM_SendToDataIT(I2C_Handle_t *pI2C_Handle,uint8_t data,uint8_t ByteNumber,uint8_t PageNumber)
{
	uint8_t arr[2]={ByteNumber,data};
	uint8_t address=EEPROM_ADDRESS | (PageNumber);

	while(I2C_MasterSendDataIT(pI2C_Handle,arr, sizeof(arr), address)!=I2C_Ready);

	_delay_ms(10);
}
void EEPROM_ReceiveFromDataIT(I2C_Handle_t *pI2C_Handle,uint8_t *data,uint8_t ByteNumber,uint8_t PageNumber)
{
	uint8_t address=EEPROM_ADDRESS | (PageNumber);
	(pI2C_Handle->TxRxState)=4;
	while(I2C_MasterSendDataIT(pI2C_Handle,&ByteNumber, 1, address)!=I2C_Ready);

	while(I2C_MasterRecieveDataIT(pI2C_Handle,data, 1, address)!=I2C_Ready);
}
