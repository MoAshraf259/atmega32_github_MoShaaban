/*
 * PB.c
 *
 *  Created on: Mar 30, 2023
 *      Author: moham
 */

//void PB_Init(DIO_Handle_t *pPBHandle)


#include "PB.h"



void PB_Init(DIO_RegDef_t *pDIOx  ,  uint8_t PinNumber  ,  uint8_t mode)
{
	DIO_Handle_t PushButton_Handle;

	PushButton_Handle.pDIOx=pDIOx;

	PushButton_Handle.DIO_Config.MODE=INPUT;
	PushButton_Handle.DIO_Config.PinNumber=PinNumber;
	if(mode ==INPUT_PU_RES)
	{
		PushButton_Handle.DIO_Config.PUPD=INPUT_PU_RES;
	}
	else if(mode==INPUT_PD_RES)
	{
		PushButton_Handle.DIO_Config.PUPD=INPUT_PD_RES;
	}
	DIO_Init(&PushButton_Handle);
}


