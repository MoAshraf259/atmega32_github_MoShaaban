/*
 * 7SEGMENT.c

 *
 *  Created on: Mar 25, 2023
 *      Author: m7mda
 */

#include "7SEGMENT.h"




void SSD_Init(DIO_Handle_t *pSSD_Handle)
{
	DIO_InitPort(pSSD_Handle);
}
void SSDDispNum(DIO_RegDef_t *pDIO,uint8_t value)
{
#if SSDType==CA
	{
		switch(value)
		{
		case 0:
			DIO_WriteToPort(pDIO, ZERO);
			break;

		case 1:
			DIO_WriteToPort(pDIO, ONE);
			break;

		case 2:
			DIO_WriteToPort(pDIO, TWO);
			break;

		case 3:
			DIO_WriteToPort(pDIO, THREE);
			break;

		case 4:
			DIO_WriteToPort(pDIO, FOUR);
			break;

		case 5:
			DIO_WriteToPort(pDIO, FIVE);
			break;

		case 6:
			DIO_WriteToPort(pDIO, SIX);
			break;

		case 7:
			DIO_WriteToPort(pDIO, SEVEN);
			break;

		case 8:
			DIO_WriteToPort(pDIO, EIGHT);
			break;

		case 9:
			DIO_WriteToPort(pDIO, NINE);
			break;
		}
	}

#elif SSDType==CC
	{
		switch(value)
		{
		case 0:
			DIO_WriteToPort(pDIO, ~ZERO);
			break;

		case 1:
			DIO_WriteToPort(pDIO, ~ONE);
			break;

		case 2:
			DIO_WriteToPort(pDIO, ~TWO);
			break;

		case 3:
			DIO_WriteToPort(pDIO, ~THREE);
			break;

		case 4:
			DIO_WriteToPort(pDIO, ~FOUR);
			break;

		case 5:
			DIO_WriteToPort(pDIO, ~FIVE);
			break;

		case 6:
			DIO_WriteToPort(pDIO, ~SIX);
			break;

		case 7:
			DIO_WriteToPort(pDIO, ~SEVEN);
			break;

		case 8:
			DIO_WriteToPort(pDIO, ~EIGHT);
			break;

		case 9:
			DIO_WriteToPort(pDIO, ~NINE);
			break;
		}
	}
#endif
}
