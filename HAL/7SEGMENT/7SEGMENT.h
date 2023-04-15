/*
 * 7SEGMENT.h
 *
 *  Created on: Mar 25, 2023
 *      Author: m7mda
 */

#ifndef HAL_7SEGMENT_7SEGMENT_H_
#define HAL_7SEGMENT_7SEGMENT_H_

#include "atmega32.h"

#define CC	0
#define CA	1

#define SSDType		CC
//THESE VALUES ARE FOR THE COMMON CATHODE
#define ZERO	0b01000000
#define ONE		0b01111001
#define	TWO		0b00100100
#define THREE	0b00110000
#define FOUR	0b00011001
#define FIVE	0b00010010
#define SIX		0b00000010
#define	SEVEN	0b01111000
#define EIGHT	0b00000000
#define	NINE	0b00010000


//uint8_t numbers[10]={0b1000000,0b1111001,0b0100100,0b0110000,0b0011001,0b0010010,0b0000010,0b1111000,0b0000000,0b0010000};
void SSD_Init(DIO_Handle_t *pSSD_Handle);

void SSDDispNum(DIO_RegDef_t *pDIO,uint8_t value);

#endif /* HAL_7SEGMENT_7SEGMENT_H_ */
