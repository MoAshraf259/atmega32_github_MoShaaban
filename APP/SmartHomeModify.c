/*
 * SmartHomeModify.c
 *
 *  Created on: Apr 14, 2023
 *      Author: moham
 */


#include "atmega32.h"
#include "LCD.h"

#define CLOSE_DOOR		1
#define OPEN_DOOR		2

void TIMER1_InterruptApp(void);
void USART_RXApp(void);
void USART_TXApp(void);


DIO_Handle_t DIO1_Handle;

void DISABLE_TIMER1(void)
{
	TIMER1->TCCR1B &= ~(0x7);
}
void DIO_MainInit(void)
{
	DIO1_Handle.pDIOx=DIOC;
	DIO1_Handle.DIO_Config.MODE=OUTPUT;
	DIO1_Handle.DIO_Config.PinNumber=BIT_NUM_0;
	DIO_Init(&DIO1_Handle);

	DIO1_Handle.pDIOx=DIOB;
	DIO1_Handle.DIO_Config.MODE=OUTPUT;
	DIO1_Handle.DIO_Config.PinNumber=BIT_NUM_0;
	DIO_Init(&DIO1_Handle);

	DIO1_Handle.DIO_Config.PinNumber=BIT_NUM_1;
	DIO_Init(&DIO1_Handle);

	DIO1_Handle.DIO_Config.PinNumber=BIT_NUM_2;
	DIO_Init(&DIO1_Handle);

	DIO1_Handle.pDIOx=DIOD;
	DIO1_Handle.DIO_Config.PinNumber=BIT_NUM_5;
	DIO_Init(&DIO1_Handle);
}

USART_Config_t USART1_Config;
void USART_MainInit(void)
{
	USART1_Config.SyncAsync=USART_Async;
	USART1_Config.CharSize=USART_CharSize_8;
	USART1_Config.Polarity=USART_Polarity_Falling;
	USART1_Config.StopBits=USART_StopBits_1;
	USART1_Config.mode=USART_Mode_RxTx;
	USART1_Config.parity=USART_Parity_Off;
	USART1_Config.BaudRate=USART_Baudrate_9600;

	USART_Init(&USART1_Config);
}

ADC_Config_t ADC1_Config;

void ADC1_Init(void)
{
	ADC1_Config.PowerSource=ADC_Power_AVCC;
	ADC1_Config.ReadFirst=ADC_FirstRead_ADCH;
	ADC1_Config.mode=ADC_Mode_Polling;
	ADC1_Config.prescaler=ADC_Prescaler_128;
	ADC1_Config.Resolution=ADC_Res_10BIT;
	ADC_Init(&ADC1_Config);
}

TIMER1_Config_t TIMER1PWM_Config;
void TIMER1_PWMMainConfig(void)
{
	TIMER1PWM_Config.Mode=TIMER1_Mode_FastPWM_ICR;
	TIMER1PWM_Config.FastPWM_Mode=TIMER1_FastPWM_NonInverted;
	TIMER1PWM_Config.Channel=Channel_A;
	TIMER1PWM_Config.Prescaler=TIMER1_Prescaler8;
	TIMER1PWM_Config.InputCaptureValue=20000;
	TIMER1_ServoPWM(0);
	TIMER1_Init(&TIMER1PWM_Config);
}


TIMER1_Config_t TIMER1Delay_Config;
void TIMER1_DelayMainConfig(void)
{
	TIMER1Delay_Config.Mode=TIMER1_Mode_CTC;
	TIMER1Delay_Config.CompareMode=TIMER1_NonPWM_Normal;
	TIMER1Delay_Config.Prescaler=TIMER1_Prescaler1024;
	TIMER1_Init(&TIMER1Delay_Config);

}
uint8_t TRYAGAIN1[]="Attempts left : 1 Enter ID Again : ";
uint8_t TRYAGAIN2[]="Attempts left : 2 Enter ID Again : ";

uint8_t WELCOME[]="Welcome Enter password :";
uint8_t WRONG_ID[]="Wrong ID !";
uint8_t startup[]="Hello Enter your ID:";
uint8_t RxMsg=0;
uint8_t TempNotification[]="Current temp:";
uint8_t temp_check[9];
uint8_t ID[]="MOASHRAF";
uint8_t PASSWORD[]="12345";

int main(void)
{
	uint32_t Temperature=0;
	DIO_MainInit();
	LCD_Init();
	USART_MainInit();
	ADC1_Init();
	LCD_SendString(TempNotification);
	USART_SendData(&USART1_Config, startup, sizeof(startup));
	USART_RecieveDataIT(USART_RXApp);
	TIMER1_PWMMainConfig();
	while(1)
	{
		ADC_StartConversionSync(ADC_ChannelNumber0);
		Temperature=ADC_Read(&ADC1_Config);
		Temperature=(((uint32_t)Temperature*500)/1024);
		lcd_set_cursor(1, 14);
		LCD_SendNumber(Temperature);
		if(Temperature>37)
		{
			DIO_WriteToPin(DIOC, 0, HIGH);
		}
		else
		{
			DIO_WriteToPin(DIOC, 0, LOW);
		}
	}
}

void USART_RXApp(void)
{
	static uint8_t flag=0;
	//static uint8_t wrong=0;
	static uint8_t attempt=3;
	static uint8_t i=0;
	RxMsg=USART->UDR;
	static uint8_t state=0;
	if(state==0)
	{

		temp_check[i]=RxMsg;
		i++;
		if(i==8)
		{
			for(uint8_t x=0;i<8;i++)
			{
				if(temp_check[x]==ID[x])
				{
					flag++;
				}

			}
			if(flag==8)
			{
				state=1;
				USART_SendData(&USART1_Config, WELCOME, sizeof(WELCOME));
			}
			else
			{
				USART_SendData(&USART1_Config, WRONG_ID, sizeof(WRONG_ID));
				attempt--;
				if(attempt==2)
				{
					USART_SendData(&USART1_Config, TRYAGAIN2, sizeof(TRYAGAIN2));
				}
				else if(attempt==1)
				{
					USART_SendData(&USART1_Config, TRYAGAIN1, sizeof(TRYAGAIN1));
				}
				else if(attempt==0)
				{
					while(1)
					{

					}
				}

			}

		}
	}
	else if(state ==1)
	{
		if(RxMsg=='1')
			{

				TIMER1_ServoPWM(0);

			}
			else if(RxMsg=='2')
			{

				TIMER1_ServoPWM(180);

			}
			else if(RxMsg=='3')
			{
				DIO_TogglePin(DIOB, 0);
			}
			else if(RxMsg=='4')
			{
				DIO_TogglePin(DIOB, 1);
			}
			else if(RxMsg=='5')
			{
				DIO_TogglePin(DIOB, 2);
			}
	}


}

void TIMER1_InterruptApp(void)
{

}

void USART_TXApp(void)
{

}
