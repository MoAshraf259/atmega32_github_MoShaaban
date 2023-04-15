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







int main(){
	LCD_Init();

	LCD_SendNumber(1547);
	while(1)
	{

	}
}




