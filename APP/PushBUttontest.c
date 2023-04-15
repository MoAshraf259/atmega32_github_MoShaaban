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

	uint8_t counter=1;
	PB_Init(DIOA, BIT_NUM_0 , INPUT_PU_RES);

	while(1)
	{
		if(! DIO_ReadFromPin(DIOA, BIT_NUM_0))
		{
			_delay_ms(75);
			counter++;
			LCD_SendChar(1);
		}

	}
}
