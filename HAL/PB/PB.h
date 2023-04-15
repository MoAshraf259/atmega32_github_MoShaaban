/*
 * PB.h
 *
 *  Created on: Mar 30, 2023
 *      Author: moham
 */

#ifndef HAL_PB_PB_H_
#define HAL_PB_PB_H_

#include "../../MCAL/atmega32.h"

void PB_Init(DIO_RegDef_t *pDIOx,uint8_t PinNumber,uint8_t mode);


#endif /* HAL_PB_PB_H_ */
