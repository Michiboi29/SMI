/*
 * pwm.h
 *
 *  Created on: 11 déc. 2021
 *      Author: eti52
 */

#ifndef PWM_H_
#define PWM_H_

float ARR;
//float dutycycle;
void configureTIM2(float p_frequence);
void changePWM(float p_dutyclye);
void configureGPIOLED();

#endif /* PWM_H_ */
