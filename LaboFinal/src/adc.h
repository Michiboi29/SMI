/*
 * adc.h
 *
 *  Created on: 11 déc. 2021
 *      Author: eti52
 */

#ifndef ADC_H_
#define ADC_H_

#include "stm32f4xx.h"
#include "macros_utiles.h"

void configureADC();
void configureGPIOADC();
void configureChannel0ADC();
void configureChannel1ADC();
uint16_t readADC(uint8_t channel);

#endif /* ADC_H_ */
