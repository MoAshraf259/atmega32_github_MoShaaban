/*
 * LED.h
 *
 *  Created on: Mar 25, 2023
 *      Author: m7mda
 */

#ifndef HAL_LED_LED_H_
#define HAL_LED_LED_H_

#include <stdint.h>
#include <stdio.h>
#include "atmega32.h"
#include <util/delay.h>
#include "7SEGMENT.h"

void LEDs_Flash(void);
void LEDs_ShiftLeft(void);
void LEDs_ShiftRight(void);
void LEDs_Converging(void);
void LEDs_Disverging(void);
void IncrementingSnakeEffect(void);
void PingPong(void);
void LEDsConvergingDisverging(void);

void TrafficLights(void);

#endif /* HAL_LED_LED_H_ */
