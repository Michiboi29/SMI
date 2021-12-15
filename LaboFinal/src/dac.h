/*
 * dac.h
 *
 *  Created on: 12 déc. 2021
 *      Author: eti52
 */

#include "stm32f4xx.h"
#include "macros_utiles.h"

#ifndef DAC_H_
#define DAC_H_
void configureGPIODAC();
void configureDAC();
void writeDAC(uint16_t value);

#endif /* DAC_H_ */
