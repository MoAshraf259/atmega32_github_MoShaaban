/*
 * DCMotor.c
 *
 *  Created on: Apr 3, 2023
 *      Author: moham
 */

#include "DCMotor.h"

void DCMotor_Init(void)
{
	DIO_Handle_t DC_Handle;
	DC_Handle.pDIOx=DC_Port;

	DC_Handle.DIO_Config.MODE=OUTPUT;

	DC_Handle.DIO_Config.PinNumber=DC_MotorPin1;
	DIO_Init(&DC_Handle);

	DC_Handle.DIO_Config.PinNumber=DC_MotorPin2;
	DIO_Init(&DC_Handle);

}
void DCMotor_Rotate(uint8_t direction)
{
	switch (direction){

	case DC_ClockWise:
		DIO_WriteToPin(DC_Port, DC_MotorPin1, LOW);
		DIO_WriteToPin(DC_Port, DC_MotorPin2, HIGH);
		break;

	case DC_CounterClockWise:
		DIO_WriteToPin(DC_Port, DC_MotorPin1, HIGH);
		DIO_WriteToPin(DC_Port, DC_MotorPin2, LOW);
		break;

	case STOP:
		DIO_WriteToPin(DC_Port, DC_MotorPin1, LOW);
		DIO_WriteToPin(DC_Port, DC_MotorPin2, LOW);
		break;
	}
}
