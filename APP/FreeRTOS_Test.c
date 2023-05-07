/*
 * FreeRTOS.c
 *
 *  Created on: Apr 18, 2023
 *      Author: moham
 */
#include "atmega32.h"
#include "LCD.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"


//Binary semaphore for the LCDs we have
xSemaphoreHandle LCD_Semaphore;


DIO_Handle_t DIO1_Handle;

void DIO1_MainInit(void)
{
	DIO1_Handle.pDIOx=DIOA;
	DIO1_Handle.DIO_Config.MODE=OUTPUT;

	DIO1_Handle.DIO_Config.PinNumber=BIT_NUM_0;
	DIO_Init(&DIO1_Handle);

	DIO1_Handle.DIO_Config.PinNumber=BIT_NUM_1;
	DIO_Init(&DIO1_Handle);

	DIO1_Handle.DIO_Config.PinNumber=BIT_NUM_2;
	DIO_Init(&DIO1_Handle);
}

void LCD1(void *pvoid);
void LCD2(void *pvoid);
void LED3(void *pvoid);

uint8_t MSG1[]="iamtask1";
uint8_t MSG2[]="mohameda";
int main(void)
{
	LCD_Init();
	DIO1_MainInit();

	//Create a binary semaphore
	LCD_Semaphore=xSemaphoreCreateCounting(1,1);


	xTaskCreate(&LCD1,NULL,200,NULL,0,NULL);   //lowest priority
	xTaskCreate(&LCD2,NULL,200,NULL,0,NULL);   //medium priority

	vTaskStartScheduler();

	while(1)
	{

	}
}


void LCD1(void * pvoid)
{
	//to indicate the state of the semaphore pDpass or pDfail
	uint8_t semaphoreState;

	while(1)
	{
		semaphoreState=xSemaphoreTake(LCD_Semaphore,0);
		if(semaphoreState==pdPASS)
		{
			lcd_set_cursor(1,1);
			LCD_SendString(MSG1);
			//Give back the semaphore taken
			xSemaphoreGive(LCD_Semaphore);

		}
		//only if the semaphore state indicates pDfail
		else
		{
			//Do NOTING !
		}
		vTaskDelay(600);
	}
}

void LCD2(void * pvoid)
{
	//to indicate the state of the semaphore pDpass or pDfail
	uint8_t semaphoreState;

	while(1)
	{
		semaphoreState=xSemaphoreTake(LCD_Semaphore,0);
		if(semaphoreState==pdPASS)
		{

			lcd_set_cursor(2, 1);
			LCD_SendString(MSG2);
			//Give back the semaphore taken
			xSemaphoreGive(LCD_Semaphore);

		}
		//only if the semaphore state indicates pDfail
		else
		{
			//Do NOTING !
		}
		vTaskDelay(600);
	}
}

void LED3(void * pvoid)
{
	while(1)
	{
		DIO_TogglePin(DIOA, 2);
		vTaskDelay(4000);
	}
}
