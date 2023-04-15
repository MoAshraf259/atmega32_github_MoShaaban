/*
 * atmega32_spi.c
 *
 *  Created on: Mar 23, 2023
 *      Author: m7mda
 */


#include "../../MCAL/SPI/atmega32_spi.h"

void (*SPIGlobalCallBack)(void)=NULL;

void SPI_Init(SPI_Config_t *SPIConfig)
{

	uint8_t temp_reg=0;
		//Configure the spi mode SLAVE OR MASTER
	temp_reg |= SPIConfig->SPI_Mode<<SPI_SPCR_MSTR;

		//Configure the interrupt for the SPI
	temp_reg |= SPIConfig->SPI_SyncAsync<<SPI_SPCR_SPIE;
	EnableGlobalInterrupt();


	//This part is to configure the Polarity of the clock rising or falling
	temp_reg |= SPIConfig->ClockPolarity<<SPI_SPCR_CPOL;

	//This part is to configure the phase of the clock setup or or sample
	temp_reg|= SPIConfig->ClockPhase<<SPI_SPCR_CPHA;

	//this part is to configure the data order
	temp_reg |= SPIConfig->DataOrder << SPI_SPCR_DORD;


	SPI->SPCR =temp_reg; // set the values on the SPCR Register



	//This part is to configure the Prescaler of the Communication
	if(SPIConfig->Prescaler==SPI_Prescaler_2)
	{
		SPI->SPCR &= ~(3<<SPI_SPCR_SPR0);
		SPI->SPSR |= (1<<SPI_SPSR_SPI2X);
	}

	else if(SPIConfig->Prescaler==SPI_Prescaler_4)
	{
		SPI->SPCR &= ~(3<<SPI_SPCR_SPR0);
		SPI->SPSR &= ~(1<<SPI_SPSR_SPI2X);
	}

	else if(SPIConfig->Prescaler==SPI_Prescaler_8)
	{
		SPI->SPCR |= (1<<SPI_SPCR_SPR0);
		SPI->SPSR |= (1<<SPI_SPSR_SPI2X);
	}

	else if(SPIConfig->Prescaler==SPI_Prescaler_16)
	{
		SPI->SPCR |= (1<<SPI_SPCR_SPR0);
		SPI->SPSR &= ~(1<<SPI_SPSR_SPI2X);
	}

	else if(SPIConfig->Prescaler==SPI_Prescaler_32)
	{
		SPI->SPCR |= (2<<SPI_SPCR_SPR0);
		SPI->SPSR |= (1<<SPI_SPSR_SPI2X);
	}

	else if(SPIConfig->Prescaler==SPI_Prescaler_64)
	{
		SPI->SPCR |= (3<<SPI_SPCR_SPR0);
		SPI->SPSR |= (1<<SPI_SPSR_SPI2X);
	}

	else if(SPIConfig->Prescaler==SPI_Prescaler_128)
	{
		SPI->SPCR |= (3<<SPI_SPCR_SPR0);
		SPI->SPSR &= ~(1<<SPI_SPSR_SPI2X);
	}

	//Enable the SPI Peripheral
	SPI->SPCR |= (1<<SPI_SPCR_SPE);
	/******************************************Done ***************************************/

}

void SPI_MasterSendData(uint8_t *pTxBuffer,uint32_t Length)
{
	while(Length !=0)
	{
		//Loading the data from the Buffer (The place the user stored the data he wants to send !)
		SPI->SPDR = *pTxBuffer;
		while((SPI->SPSR >> SPI_SPSR_SPIF) & 0x1);
		pTxBuffer++;//Increasing the buffer address to get the next byte
		Length--;//Decreasing the length to reach the range
	}

}
void SPI_MasterReceiveData(uint8_t *pRxBuffer,uint32_t Length)
{
	while(Length!=0)
	{
		//Loading the data from the Data Register to the Buffer
		while((SPI->SPSR >> SPI_SPSR_SPIF) & 0x1);
		*pRxBuffer = SPI->SPDR;

		pRxBuffer++;//Increasing the buffer address to get the next byte
		Length--;//Decreasing the length to reach the range
	}
}

uint8_t SPI_Trans(uint8_t *pRxBuffer)
{
	SPI->SPDR = *pRxBuffer;
	while((SPI->SPSR >> SPI_SPSR_SPIF) & 0x1);

	return SPI->SPDR;
}

void SPI_SendIT(uint8_t *pTxBuffer,void (*pCallBack)(void),uint8_t Length)
{
	SPIGlobalCallBack=pCallBack;
	while(Length!=0)
	{
		DIO_WriteToPin(DIOD, 4, LOW);//slave select pin
		SPI->SPDR=*pTxBuffer;
		_delay_ms(10);
		DIO_WriteToPin(DIOD, 4, HIGH);
		pTxBuffer++;
		Length--;
	}

}

void SPI_RecieveIT(void (*pCallBack)(void))
{
	SPIGlobalCallBack=pCallBack;
}

//SPI IRQ Transfer completed !
void __vector_12(void) __attribute__((signal));
void __vector_12(void)
{
	SPIGlobalCallBack();
}
