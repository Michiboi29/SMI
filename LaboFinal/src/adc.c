/*
 * adc.c
 *
 *  Created on: 11 déc. 2021
 *      Author: eti52
 */
#include "stm32f4xx.h"
#include "macros_utiles.h"
#include "adc.h"

void configureADC(){

	RCC->APB2ENR |= BIT8; //enable ADC1 clock

	ADC1->CR1 &=  ~(BIT24 | BIT25); // Res 12 bit -- 15 ADCCLK cycles



}

void configureGPIOADC(){
	RCC->AHB1ENR |= BIT0; // Enable GPIOA clock

	GPIOA->MODER |= (BIT0 | BIT1); // Mode Analog pin0
	GPIOA->OTYPER &= ~BIT0; // push-pusll pin0
	GPIOA->PUPDR |= BIT1;  // pull-down pin0
	GPIOA->PUPDR &= ~BIT0;

	GPIOA->OSPEEDR |= BIT0;	//medium speed pin0
	GPIOA->OSPEEDR &= ~BIT1;
}
