/*
 * keypad.c
 *
 *  Created on: Mar 31, 2023
 *      Author: moham
 */

#include "keypad.h"



void Keypad_Init(void)
{
	DIO_Handle_t Keypad_Handle;

	Keypad_Handle.pDIOx=KEYPAD_PORT;

	Keypad_Handle.DIO_Config.MODE=OUTPUT;

	Keypad_Handle.DIO_Config.PinNumber=KEYPAD_R0;
	DIO_Init(&Keypad_Handle);

	Keypad_Handle.DIO_Config.PinNumber=KEYPAD_R1;
	DIO_Init(&Keypad_Handle);

	Keypad_Handle.DIO_Config.PinNumber=KEYPAD_R2;
	DIO_Init(&Keypad_Handle);

	Keypad_Handle.DIO_Config.PinNumber=KEYPAD_R3;
	DIO_Init(&Keypad_Handle);

	Keypad_Handle.DIO_Config.MODE=INPUT;
	Keypad_Handle.DIO_Config.PUPD=INPUT_PU_RES;

	Keypad_Handle.DIO_Config.PinNumber=KEYPAD_C0;
	DIO_Init(&Keypad_Handle);

	Keypad_Handle.DIO_Config.PinNumber=KEYPAD_C1;
	DIO_Init(&Keypad_Handle);

	Keypad_Handle.DIO_Config.PinNumber=KEYPAD_C2;
	DIO_Init(&Keypad_Handle);

	Keypad_Handle.DIO_Config.PinNumber=KEYPAD_C3;
	DIO_Init(&Keypad_Handle);

}

uint8_t Keypad_GetPressed(void)
{
	//WE will be checking on the Columns
	uint8_t Pressed_Key=0;
	uint8_t temp_val;

	uint8_t KEYPAD_ARR[4][4]=KPD_VALUES;

	uint8_t KEYPAD_ROW[4]={KEYPAD_R0,KEYPAD_R1,KEYPAD_R2,KEYPAD_R3};
	uint8_t KEYPAD_COL[4]={KEYPAD_C0,KEYPAD_C1,KEYPAD_C2,KEYPAD_C3};

	for(uint8_t row=0;row<4;row++)
	{
		DIO_WriteToPin(KEYPAD_PORT, KEYPAD_ROW[row], LOW);

		for(uint8_t col=0;col<4;col++)
		{
			temp_val=DIO_ReadFromPin(KEYPAD_PORT, KEYPAD_COL[col]);

			if(temp_val==LOW){
			Pressed_Key=KEYPAD_ARR[row][col];
			}
		}
		DIO_WriteToPin(KEYPAD_PORT, KEYPAD_ROW[row], HIGH);
	}

	return Pressed_Key;
}

