/*
 * atmega32_i2c.c
 *
 *  Created on: Apr 11, 2023
 *      Author: moham
 */


#include "atmega32_i2c.h"
//Helper Functions for the .c File of the I2C
void I2C_GenerateStartCond(void);
void I2C_GenerateStopCond(void);
void I2C_EnablePeripheral(void);


void I2C_Init(I2C_Config_t *pI2C_Config)
{
	//Enabling or Disabling the interrupt for the I2C Depending on the macro given by the user in main app
	EnableGlobalInterrupt();
	TWCR |= pI2C_Config->I2C_Mode << I2C_TWCR_TWIE;

	//Enabling or Disabling the ACK bit
	TWCR |= pI2C_Config->I2C_Ack << I2C_TWCR_TWEA;

	//Setting it`s own address so if another master wants to communicate with it as a slave
	I2C->TWAR = (pI2C_Config->I2C_Address << 1);

	//Enabling or disabling the GENERAL call respond from this target
	I2C->TWAR |= (pI2C_Config->GenralCall_Status<<I2C_TWAR_TWGCE);

	if(pI2C_Config->I2C_Prescaler == I2C_SCL_SPEED400K)
	{
		I2C->TWBR = 2;
		I2C->TWSR &= ~(3<<I2C_TWSR_TWPS0);
	}
	else if(pI2C_Config->I2C_Prescaler == I2C_SCL_SPEED200K)
	{
		I2C->TWBR = 12;
		I2C->TWSR &= ~(3<<I2C_TWSR_TWPS0);
	}
	else if(pI2C_Config->I2C_Prescaler == I2C_SCL_SPEED100K)
	{
		I2C->TWBR = 32;
		I2C->TWSR &= ~(3<<I2C_TWSR_TWPS0);
	}


	//Enabling the I2C  Peripheral
	I2C_EnablePeripheral();
}

void I2C_MasterSendData(I2C_Config_t *pI2C_Config,uint8_t *pTxBuffer,uint8_t Length,uint8_t Address)
{
	I2C_GenerateStartCond();
	I2C->TWDR =(Address<<1)& ~(0x1);

	while(Length!=0)
	{
		I2C->TWDR = *pTxBuffer;
		pTxBuffer++;
		Length--;
	}
	I2C_GenerateStopCond();


}
void I2C_MasterRecieveData(I2C_Config_t *pI2C_Config,uint8_t *pRxBuffer,uint8_t Length , uint8_t Address)
{
	I2C_GenerateStartCond();
	I2C->TWDR =(Address<<1) |(0x1);

	while(Length!=0)
		{
			*pRxBuffer = I2C->TWDR;
			pRxBuffer++;
			Length--;
		}
		I2C_GenerateStopCond();

}
void I2C_GenerateStartCond(void)
{
	TWCR |= (1<<I2C_TWCR_TWSTA);
}
void I2C_GenerateStopCond(void)
{
	TWCR |= (1<<I2C_TWCR_TWSTO);
}

void I2C_EnablePeripheral(void)
{
	TWCR |= (1<<I2C_TWCR_TWEN);
}

void I2C_ISRHandler(void)
{
	switch (I2C->TWSR & STATUS_MASK)
	{
	case START_ACK:
		TWCR |= (1<<I2C_TWCR_TWINT);
		break;

	case REP_START_ACK:
		TWCR |= (1<<I2C_TWCR_TWINT);
		break;

	case SLAVE_ADDR_AND_WR_ACK:
		TWCR |= (1<<I2C_TWCR_TWINT);
		break;

	case SLAVE_ADDR_AND_RD_ACK:
		TWCR |= (1<<I2C_TWCR_TWINT);
		break;

	case MSTR_WR_BYTE_ACK:
		TWCR |= (1<<I2C_TWCR_TWINT);
		break;

	case MSTR_RD_BYTE_WITH_ACK:
		TWCR |= (1<<I2C_TWCR_TWINT);
		break;

	case MSTR_RD_BYTE_WITH_NACK:
		TWCR |= (1<<I2C_TWCR_TWINT);
		break;

	case SLAVE_ADDR_RCVD_RD_REQ:
		TWCR |= (1<<I2C_TWCR_TWINT);
		break;

	case SLAVE_ADDR_RCVD_WR_REQ:
		TWCR |= (1<<I2C_TWCR_TWINT);
		break;

	case SLAVE_DATA_RECEIVED:
		TWCR |= (1<<I2C_TWCR_TWINT);
		break;

	case SLAVE_BYTE_TRANSMITTED:
		TWCR |= (1<<I2C_TWCR_TWINT);
		break;

	default :
		break;

	}
}
void __vector_19(void) __attribute__((signal));
void __vector_19(void)
{
	I2C_ISRHandler();
}
