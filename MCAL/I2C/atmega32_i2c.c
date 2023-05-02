/*
 * atmega32_i2c.c
 *
 *  Created on: Apr 11, 2023
 *      Author: moham
 */


#include "atmega32_i2c.h"

//Helper Functions for the .c File of the I2C
static void I2C_ExcutePhaseAddress(I2C_Handle_t *pI2C_Handle);
static void I2C_HandleTXEMaster(I2C_Handle_t *pI2C_Handle);
static void I2C_HandleRXEMaster(I2C_Handle_t *pI2C_Handle);

static void I2C_GenerateStartCond(void);
static void I2C_EnablePeripheral(void);
static void I2C_GenerateStopCond(void);

void I2C_Init(I2C_Handle_t *pI2C_Handle)
{
	//Enabling or Disabling the interrupt for the I2C Depending on the macro given by the user in main app
	if(pI2C_Handle->pI2C_Config.I2C_Mode==I2C_Mode_Sync)
	{
		/*Do nothing*/
	}
	else if(pI2C_Handle->pI2C_Config.I2C_Mode==I2C_Mode_Async)
	{
	EnableGlobalInterrupt();
	TWCR |=pI2C_Handle->pI2C_Config.I2C_Mode << I2C_TWCR_TWIE;
	}

	//Enabling or Disabling the ACK bit
	TWCR |= pI2C_Handle->pI2C_Config.I2C_Ack << I2C_TWCR_TWEA;

	//Setting it`s own address so if another master wants to communicate with it as a slave
	I2C->TWAR = (pI2C_Handle->pI2C_Config.I2C_Address << 1);

	//Enabling or disabling the GENERAL call respond from this target
	I2C->TWAR |= (pI2C_Handle->pI2C_Config.GenralCall_Status<<I2C_TWAR_TWGCE);

	if(pI2C_Handle->pI2C_Config.I2C_Prescaler == I2C_SCL_SPEED400K)
	{
		I2C->TWBR = 2;
		I2C->TWSR &= ~(3<<I2C_TWSR_TWPS0);
	}
	else if(pI2C_Handle->pI2C_Config.I2C_Prescaler == I2C_SCL_SPEED200K)
	{
		I2C->TWBR = 12;
		I2C->TWSR &= ~(3<<I2C_TWSR_TWPS0);
	}
	else if(pI2C_Handle->pI2C_Config.I2C_Prescaler == I2C_SCL_SPEED100K)
	{
		I2C->TWBR = 32;
		I2C->TWSR &= ~(3<<I2C_TWSR_TWPS0);
	}


	//Enabling the I2C  Peripheral
	I2C_EnablePeripheral();
}


void I2C_MasterSendData(uint8_t *pTxBuffer,uint8_t Length,uint8_t Address)
{
	I2C_GenerateStartCond();
	while ((I2C->TWSR & STATUS_MASK )!=(START_ACK));

	I2C->TWDR =(Address<<1)& ~(0x1);
	while ((I2C->TWSR & STATUS_MASK )!=(SLAVE_ADDR_AND_WR_ACK));

	while(Length!=0)
	{
		I2C->TWDR = *pTxBuffer;
		while ((I2C->TWSR & STATUS_MASK )!=(MSTR_WR_BYTE_ACK));
		pTxBuffer++;
		Length--;
	}

}
void I2C_MasterRecieveData(uint8_t *pRxBuffer,uint8_t Length, uint8_t Address)
{
	I2C_GenerateStartCond();
	while ((I2C->TWSR & STATUS_MASK )!=(START_ACK));

	I2C->TWDR =(Address<<1) |(0x1);
	while ((I2C->TWSR & STATUS_MASK )!=(SLAVE_ADDR_AND_RD_ACK));

		while(Length!=0)
			{
				*pRxBuffer = I2C->TWDR;
				while ((I2C->TWSR & STATUS_MASK )!=(MSTR_RD_BYTE_WITH_ACK));
				pRxBuffer++;
				Length--;
			}

}

uint8_t I2C_MasterSendDataIT(I2C_Handle_t *pI2C_Handle,uint8_t *pTxBuffer,uint8_t Length,uint8_t Address)
{
	//Checking if the program is free to use I2C or not
	uint8_t busystate=pI2C_Handle->TxRxState;
	if(busystate != Busy_In_Rx && busystate != Busy_In_Tx)
	{
	pI2C_Handle->TxRxState=Busy_In_Tx;//Reserving the i2c for TX
	pI2C_Handle->pTxBuffer=pTxBuffer;
	pI2C_Handle->RxSize=Length;
	pI2C_Handle->DevAddr=Address;

	I2C_GenerateStartCond();
	}

	return busystate;//if this function in main returned I2C_Ready then it reached LINE 220
}

uint8_t I2C_MasterRecieveDataIT(I2C_Handle_t *pI2C_Handle,uint8_t *pRxBuffer,uint8_t Length , uint8_t Address)
{
	//Checking if the program is free to use I2C or not
	uint8_t busystate=pI2C_Handle->TxRxState;
	if(busystate != Busy_In_Rx && busystate!= Busy_In_Tx)
	{
		pI2C_Handle->DevAddr=Address;
		pI2C_Handle->RxSize=Length;
		pI2C_Handle->pRxBuffer=pRxBuffer;
		pI2C_Handle->TxRxState=Busy_In_Rx;

		I2C_GenerateStartCond();
	}

	return busystate;//if this function in main returned I2C_Ready then it reached LINE 235
}



void I2C_ISRHandler(I2C_Handle_t *pI2C_Handle)
{
	switch (I2C->TWSR & STATUS_MASK)
	{
	case START_ACK:
		I2C_ExcutePhaseAddress(pI2C_Handle);
		TWCR |= (1<<I2C_TWCR_TWINT);
		break;

	case SLAVE_ADDR_AND_WR_ACK:
		I2C_HandleTXEMaster(pI2C_Handle);
		TWCR |= (1<<I2C_TWCR_TWINT);
		break;

	case MSTR_WR_BYTE_ACK:
		I2C_HandleTXEMaster(pI2C_Handle);
		TWCR |= (1<<I2C_TWCR_TWINT);
		break;

	case REP_START_ACK:
		TWCR |= (1<<I2C_TWCR_TWINT);
		break;


	case SLAVE_ADDR_AND_RD_ACK:
		I2C_HandleRXEMaster(pI2C_Handle);
		TWCR |= (1<<I2C_TWCR_TWINT);
		break;

	case MSTR_RD_BYTE_WITH_ACK:
		I2C_HandleRXEMaster(pI2C_Handle);
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
		while(1);
		break;

	}
}

static void I2C_ExcutePhaseAddress(I2C_Handle_t *pI2C_Handle)
{
	if(pI2C_Handle->TxRxState==Busy_In_Rx)
	{
		I2C->TWDR =(pI2C_Handle->DevAddr<<1) |(0x1);
	}
	else if(pI2C_Handle->TxRxState==Busy_In_Tx)
	{
		I2C->TWDR =(pI2C_Handle->DevAddr<<1)& ~(0x1);
	}
}

static void I2C_HandleTXEMaster(I2C_Handle_t *pI2C_Handle)
{
	if(pI2C_Handle->TxLen>0)
	{
	I2C->TWDR = *(pI2C_Handle->pTxBuffer);
	pI2C_Handle->TxLen--;
	pI2C_Handle->pTxBuffer++;
	}
	else if(pI2C_Handle->TxLen==0)
	{
		I2C_GenerateStopCond();
		pI2C_Handle->TxRxState=I2C_Ready;
	}
}

static void I2C_HandleRXEMaster(I2C_Handle_t *pI2C_Handle)
{
	if(pI2C_Handle->RxLen >0 )
	{
		*(pI2C_Handle->pRxBuffer) = I2C->TWDR;
		pI2C_Handle->pRxBuffer++;
		pI2C_Handle->RxLen--;
	}
	else if(pI2C_Handle->RxLen==0)
	{
		I2C_GenerateStopCond();
		pI2C_Handle->TxRxState=I2C_Ready;
	}
}

static void I2C_GenerateStartCond(void)
{
	TWCR |= (1<<I2C_TWCR_TWSTA);
}

static void I2C_GenerateStopCond(void)
{
	TWCR |= (1<<I2C_TWCR_TWSTO);
}

void I2C_EnablePeripheral(void)
{
	TWCR |= (1<<I2C_TWCR_TWEN);
}


