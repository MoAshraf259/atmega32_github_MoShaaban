/*
 * LED.c
 *
 *  Created on: Mar 25, 2023
 *      Author: m7mda
 */


#include "LED.h"

DIO_Handle_t Handle_DIO;

DIO_Handle_t SSD_Handle;

void SSD_INIT1(void)
{
	SSD_Handle.DIO_Config.MODE=OUTPUT;
	SSD_Handle.pDIOx=DIOC;

	SSD_Init(&SSD_Handle);

	SSD_Handle.pDIOx=DIOA;
	SSD_Init(&SSD_Handle);

}


void LEDs_Flash()
{
	Handle_DIO.pDIOx=DIOD;

	Handle_DIO.DIO_Config.MODE=OUTPUT;

	DIO_InitPort(&Handle_DIO);
	while(DIO_ReadFromPort(DIOA)==0)
	{
	DIO_WriteToPort(DIOD, 0xFF);
	_delay_ms(500);

	DIO_WriteToPort(DIOD, 0x00);
	_delay_ms(500);

	}
}



void LEDs_ShiftLeft(void)
{
	Handle_DIO.pDIOx=DIOD;

	Handle_DIO.DIO_Config.MODE=OUTPUT;

	DIO_InitPort(&Handle_DIO);
	uint8_t temp=1;

	while(DIO_ReadFromPort(DIOA)==1)
	{
		DIO_WriteToPort(DIOD, (temp));
		temp=temp<<1;
		_delay_ms(200);

		if(temp==128)
		{
			DIO_WriteToPort(DIOD, temp);
			_delay_ms(200);
			temp=1;
		}
	}

}

void LEDs_ShiftRight(void)
{
	Handle_DIO.pDIOx=DIOD;

	Handle_DIO.DIO_Config.MODE=OUTPUT;

	DIO_InitPort(&Handle_DIO);
	uint8_t temp=128;

	while(DIO_ReadFromPort(DIOA)==2)
	{
		DIO_WriteToPort(DIOD, (temp));
		temp=temp>>1;
		_delay_ms(200);

		if(temp==1)
		{
			DIO_WriteToPort(DIOD, temp);
			_delay_ms(200);
			temp=128;
		}
	}

}

void LEDs_Converging(void)
{
	Handle_DIO.pDIOx=DIOD;

	Handle_DIO.DIO_Config.MODE=OUTPUT;

	DIO_InitPort(&Handle_DIO);

	uint8_t temp1=0x01;
	uint8_t temp2=0x80;

	while(DIO_ReadFromPort(DIOA)==3)
	{
		DIO_WriteToPort(DIOD, (temp1 | temp2));
		_delay_ms(300);
		temp1=temp1<<1;
		temp2=temp2>>1;
		if(temp1==0x10 && temp2==0x8)
		{
			temp1=0x01;
			temp2=0x80;
		}

	}
}

void LEDs_Disverging(void)
{
	Handle_DIO.pDIOx=DIOD;

	Handle_DIO.DIO_Config.MODE=OUTPUT;

		DIO_InitPort(&Handle_DIO);

		uint8_t temp1=0x08;
		uint8_t temp2=0x10;

		while(DIO_ReadFromPort(DIOA)==4)
		{
			DIO_WriteToPort(DIOD, (temp1 | temp2));
			_delay_ms(300);
			temp1=temp1>>1;
			temp2=temp2<<1;
			if(temp1==0x1 && temp2==0x80)
			{
				DIO_WriteToPort(DIOD, (temp1 | temp2));
				_delay_ms(300);
				temp1=0x08;
				temp2=0x10;
			}

		}
}

void IncrementingSnakeEffect(void)
{
	Handle_DIO.pDIOx=DIOD;

	Handle_DIO.DIO_Config.MODE=OUTPUT;

			DIO_InitPort(&Handle_DIO);

			uint8_t temp1=1;
			uint8_t x=1;
	while(DIO_ReadFromPort(DIOA)==5)
	{
		DIO_WriteToPort(DIOD, temp1);
		_delay_ms(300);
		temp1=temp1 |(x<<1);
		x=x<<1;
		if(temp1==255 && x==128)
		{
			x=1;

			for(uint8_t i=0;i<7;i++)
			{
				if(!DIO_ReadFromPort(DIOA)==5)
								{
									break;
								}
				else{
			temp1=temp1 & ~(x);
			x=x<<1;
			DIO_WriteToPort(DIOD, temp1);
			_delay_ms(300);

				}
			}

			temp1=1;
			x=1;
		}
	}

}

void PingPong(void)
{
	Handle_DIO.pDIOx=DIOD;

	Handle_DIO.DIO_Config.MODE=OUTPUT;
	DIO_InitPort(&Handle_DIO);

	uint8_t temp1=1;

	while(DIO_ReadFromPort(DIOA)==6)
	{
		DIO_WriteToPort(DIOD, temp1);
		_delay_ms(150);
		temp1=temp1<<1;

		if(temp1==128)
		{
			for(uint8_t i=0;i<8;i++){
				if(!DIO_ReadFromPort(DIOA)==6)
				{
					break;
				}
				else
				{
			DIO_WriteToPort(DIOD, temp1);
			_delay_ms(150);
			temp1=temp1>>1;
			}
			}
			temp1=1;
		}

	}
}

void LEDsConvergingDisverging(void)
{
		Handle_DIO.pDIOx=DIOD;
		Handle_DIO.DIO_Config.MODE=OUTPUT;

		DIO_InitPort(&Handle_DIO);

		uint8_t temp1=0x01;
		uint8_t temp2=0x80;

		while(DIO_ReadFromPort(DIOA)==7)
		{
			DIO_WriteToPort(DIOD, (temp1 | temp2));
			_delay_ms(150);
			temp1=temp1<<1;
			temp2=temp2>>1;
			if(temp1==0x10 && temp2==0x8)
				{

					for(uint8_t i=0;i<4;i++)
					{
						if(!DIO_ReadFromPort(DIOA)==7)
						{
							break;
						}
						else{
						DIO_WriteToPort(DIOD, (temp1 | temp2));
						_delay_ms(150);
						temp1=temp1>>1;
						temp2=temp2<<1;
						}
					}
					temp1=0x01;
					temp2=0x80;
				}


		}
}

void TrafficLights(void)
{

	Handle_DIO.pDIOx=DIOD;
	Handle_DIO.DIO_Config.MODE=OUTPUT;
	Handle_DIO.DIO_Config.PinNumber=BIT_NUM_0;
	SSD_INIT1();
	DIO_Init(&Handle_DIO);

	Handle_DIO.DIO_Config.PinNumber=BIT_NUM_1;
		DIO_Init(&Handle_DIO);

	Handle_DIO.DIO_Config.PinNumber=BIT_NUM_2;
		DIO_Init(&Handle_DIO);


		uint8_t x,y;
while(1)
	{
	uint8_t counter=10;
	while(counter>0){
x=counter%10;//The right sided SSD	PORTC
y=counter/10;//The left sided SSD	PORTA
counter--;

	DIO_WriteToPin(DIOD, 0, HIGH);//Green
	SSDDispNum(DIOA,x);
	SSDDispNum(DIOC,y);
	_delay_ms(1000);
	}

	DIO_WriteToPin(DIOD, 0, LOW);//Green



	counter=3;

	while(counter>0){
	x=counter%10;//The right sided SSD	PORTC
	y=counter/10;//The left sided SSD	PORTA
	counter--;

	DIO_WriteToPin(DIOD, 1, HIGH);//Yellow
	SSDDispNum(DIOA,x);
	SSDDispNum(DIOC,y);
	_delay_ms(1000);

	}
	DIO_WriteToPin(DIOD, 1, LOW);//Yellow


	counter=10;

	while(counter>0)
	{
		x=counter%10;//The right sided SSD	PORTC
		y=counter/10;//The left sided SSD	PORTA
		counter--;
		DIO_WriteToPin(DIOD, 2, HIGH);//RED

		SSDDispNum(DIOA,x);
		SSDDispNum(DIOC,y);
		_delay_ms(1000);

	}
	DIO_WriteToPin(DIOD, 2, LOW);//RED

	}
}
