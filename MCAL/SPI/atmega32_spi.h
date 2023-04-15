/*
 * atmega32_spi.h
 *
 *  Created on: Mar 23, 2023
 *      Author: m7mda
 */

#ifndef DRIVERS_INC_ATMEGA32_SPI_H_
#define DRIVERS_INC_ATMEGA32_SPI_H_

#include "../../MCAL/atmega32.h"


#define SPI_SLAVE			0
#define SPI_MASTER			1

#define SPI_CPOL_RISING		0
#define SPI_CPOL_FALLING	1

#define SPI_Async		1
#define SPI_Sync		0

#define SPI_CPHA_SETUP		0
#define SPI_CPHA_SAMPLE		1

#define SPI_DATAORDER_MSB	0
#define SPI_DATAORDER_LSB	1

#define SPI_Prescaler_2			0
#define SPI_Prescaler_4			1
#define SPI_Prescaler_8			2
#define SPI_Prescaler_16		3
#define SPI_Prescaler_32		4
#define SPI_Prescaler_64		5
#define SPI_Prescaler_128		6


typedef struct {

	uint8_t SPI_SyncAsync;
	uint8_t SPI_Mode;
	uint8_t ClockPolarity;
	uint8_t ClockPhase;
	uint8_t Prescaler;
	uint8_t DataOrder;
}SPI_Config_t;



void SPI_Init(SPI_Config_t *SPIConfig);

void SPI_MasterSendData(uint8_t *pTxBuffer,uint32_t Length);
void SPI_MasterReceiveData(uint8_t *pRxBuffer,uint32_t Length);

uint8_t SPI_Trans(uint8_t *pRxBuffer);
void SPI_SendIT(uint8_t *pTxBuffer,void (*pCallBack)(void),uint8_t Length);
void SPI_RecieveIT(void (*pCallBack)(void));

#endif /* DRIVERS_INC_ATMEGA32_SPI_H_ */
