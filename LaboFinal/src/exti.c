/*
 * exti.c
 *
 *  Created on: 17 déc. 2021
 *      Author: eti52
 */

#include "exti.h"

void configureGPIOEXTI(){
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN; // enable clock for syscfg

	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN; //enable clock GPIOB port

	GPIOB->MODER &= ~(BIT24 | BIT25); // Mode input pin12
	GPIOB->OTYPER &= ~BIT12; // push-pull pin12
	GPIOB->PUPDR |= BIT24;  // pull-up pin 12
	GPIOB->PUPDR &= ~BIT25;

	GPIOB->OSPEEDR |= (BIT24 | BIT25);	//very high speed pin12
}

void configureEXTI(){
	SYSCFG->EXTICR[3] |= BIT0; // pin PB12
	SYSCFG->EXTICR[3] &= ~(BIT1 | BIT2 | BIT3);

	EXTI->IMR |= BIT12;  // enable interrupt request for line 12
	EXTI->EMR &= ~BIT12; // disable event request for line 12
	EXTI->RTSR |= BIT12; // Rising trigger enabled for line 12
	EXTI->FTSR &= ~BIT12; // Falling trigger disable for line 12

	EXTI->PR |= BIT12; // update flag exti

	NVIC->ISER[1] |= BIT8; // pos 40 enable EXTI15_10 interrupt in NVIC
}


