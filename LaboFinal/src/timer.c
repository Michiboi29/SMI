/*
 * timer.c
 *
 *  Created on: 17 déc. 2021
 *      Author: eti52
 */

#include "timer.h"


void configureTIM3(float p_frequence)
{
	volatile int sys_clk = 53760000; //syscoreclk
	volatile int prescaler_1 = 500; // 1 to 512
	volatile int prescaler_2 = 2; // prescaller_2 % prescaler_3 = 4/2 = 2

	RCC->APB1ENR |= BIT1;															// clock enable
	TIM3->CR1 &= ~BIT0;																// timer disable

	TIM3->CR1 |= BIT4;																// set as downcounter

	TIM3->DIER |= BIT0;																// peripheral interrupt enable
	NVIC->ISER[0] |= BIT29;															// NVIC timer interrupt enable

	TIM3->PSC = prescaler_1;														// prescaler
	TIM3->ARR = (sys_clk/(prescaler_1*prescaler_2))/(p_frequence);					// set max value (when to interrupt)

	TIM3->CR1 |= BIT7;																// auto-reload preload

	TIM3->CR1 |= BIT0;																// timer enable
}
