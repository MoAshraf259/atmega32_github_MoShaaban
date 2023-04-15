/*
 * main.c
 *
 *  Created on: Mar 21, 2023
 *      Author: Mohamed Ashraf
 */
/********************  Mohamed Ashraf Shaaban     *****************/



#include <stdint.h>
#include <stdio.h>
#include "atmega32.h"
#include <util/delay.h>
#include "LED.h"
#include "LCD.h"
#include "keypad.h"

ISR(INT0_vect){
	LEDs_Flash();
}

EXTI_Config_t EXTI0_Config;

void EXTI_INT0_Init(void){
	EXTI0_Config.EXTI_Number=EXTI0;
	EXTI0_Config.InteruptMode=EXTI_FALLING_EDGE;

	EXTI_Init(&EXTI0_Config);
}


int main(){
	LCD_Init();
	Keypad_Init();

	uint8_t value=0;


	while(1)
	{
		value=Keypad_GetPressed();
		if(value!=0)
		{
		LCD_SendChar(value);
		}
	}
}




