/*
 * pwm.h
 *
 *  Created on: 11 déc. 2021
 *      Author: eti52
 */

#ifndef PWM_H_
#define PWM_H_
#include "stm32f4xx.h"
#include "macros_utiles.h"

float ARR;
void configureTIM2(float p_frequence);
void setPWM(float p_dutyclye);
void configureGPIOPWM();

#endif /* PWM_H_ */
