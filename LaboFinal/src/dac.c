/*
 * dac.c
 *
 *  Created on: 12 déc. 2021
 *      Author: eti52
 */

#include "dac.h"

void configureGPIODAC(){
	RCC->AHB1ENR |= BIT0; // Enable GPIOA clock

	GPIOA->MODER |= (BIT8 | BIT9); // Mode Analog pin4
	GPIOA->OTYPER &= ~BIT4; // push-pull pin4
	GPIOA->PUPDR |= BIT9;  // pull-down pin4
	GPIOA->PUPDR &= ~BIT8;

	GPIOA->OSPEEDR |= BIT5;	//high speed pin4
	GPIOA->OSPEEDR &= ~BIT4;
}

void configureDAC(){

	RCC->APB1ENR |= RCC_APB1ENR_DACEN; //enable DAC clock

	DAC->CR &= ~DAC_CR_BOFF1; // output buffer enable
	DAC->CR &= ~DAC_CR_TEN1; // trigger disable
	DAC->CR &= ~DAC_CR_WAVE1; //wave generation disable

	DAC->CR |= DAC_CR_EN1; // enable dac channel 1
}

void writeDAC(uint16_t value){
	// value cap
	if (value > 4095) {
		value = 4095;
	}
	DAC->DHR12R1 = value; // Set 12-bit value, right aligned
}
