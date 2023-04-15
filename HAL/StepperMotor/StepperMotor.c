/*
 * StepperMotor.c
 *
 *  Created on: Apr 3, 2023
 *      Author: Mohamed Ashraf
 */

#include "StepperMotor.h"


void StepperMotor_Init(void)
{
	DIO_Handle_t StepperMotor;

	StepperMotor.pDIOx=Stepper_Port;

	StepperMotor.DIO_Config.MODE=OUTPUT;

	StepperMotor.DIO_Config.PinNumber=coil_1;
	DIO_Init(&StepperMotor);

	StepperMotor.DIO_Config.PinNumber=coil_2;
	DIO_Init(&StepperMotor);

	StepperMotor.DIO_Config.PinNumber=coil_3;
	DIO_Init(&StepperMotor);

	StepperMotor.DIO_Config.PinNumber=coil_4;
	DIO_Init(&StepperMotor);

}
void StepperMotor_ControlRotation(uint8_t rotation_mode)
{
	if(rotation_mode==STOP)
	{
		DIO_WriteToPort(Stepper_Port, 0x0F);
	}


	else if(rotation_mode==CounterClockWise)
	{
		DIO_WriteToPort(Stepper_Port, 0xE);
		_delay_us(50);
		DIO_WriteToPort(Stepper_Port, 0xD);
		_delay_us(50);
		DIO_WriteToPort(Stepper_Port, 0xB);
		_delay_us(50);
		DIO_WriteToPort(Stepper_Port, 0x7);
		_delay_us(50);

	}
	else if(rotation_mode==ClockWise)
	{
		DIO_WriteToPort(Stepper_Port, 0x7);
		_delay_us(50);
		DIO_WriteToPort(Stepper_Port, 0xB);
		_delay_us(50);
		DIO_WriteToPort(Stepper_Port, 0xD);
		_delay_us(50);
		DIO_WriteToPort(Stepper_Port, 0xE);
		_delay_us(50);

	}

}
void StepperMotor_Angle(uint16_t angle,uint8_t direction)
{
	if (direction ==ClockWise){
	for(uint8_t i =0;i<=(angle/100);i++)
	{
		DIO_WriteToPort(Stepper_Port, 0x7);
		_delay_us(50);
		DIO_WriteToPort(Stepper_Port, 0xB);
		_delay_us(50);
		DIO_WriteToPort(Stepper_Port, 0xD);
		_delay_us(50);
		DIO_WriteToPort(Stepper_Port, 0xE);
		_delay_us(50);
	}
	}
	else if(direction ==CounterClockWise)
	{
		DIO_WriteToPort(Stepper_Port, 0xE);
		_delay_us(50);
		DIO_WriteToPort(Stepper_Port, 0xD);
		_delay_us(50);
		DIO_WriteToPort(Stepper_Port, 0xB);
		_delay_us(50);
		DIO_WriteToPort(Stepper_Port, 0x7);
		_delay_us(50);
	}
}
