/*
 * LM35.c
 *
 *  Created on: Apr 5, 2023
 *      Author: moham
 */

#include "LM35.h"



uint16_t LM35_Read(ADC_Config_t *pLM35_Config)
{
	uint16_t temperature =ADC_Read(pLM35_Config);
	temperature = ((uint32_t)temperature *500 )/256;
	return temperature;
}
