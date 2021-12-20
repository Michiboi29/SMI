/*
 * adc.c
 *
 *  Created on: 11 déc. 2021
 *      Author: eti52
 */
#include "adc.h"

void configureADC(){

	RCC->APB2ENR |= BIT8; //enable ADC1 clock

	ADC1->CR1 &=  ~(BIT24 | BIT25); // ADC resolution 12 bit -- 15 ADCCLK cycles
	ADC1->CR1 &=  ~BIT8; //scan mode disable

	ADC1->CR2 &= ~BIT11; // right data align
	ADC1->CR2 &= ~(BIT28 | BIT29); // disable  External trigger
	ADC1->CR2 &= ~BIT1; // single conversion mode

	ADC1->SQR1 &= ~(BIT20 | BIT21 | BIT22| BIT23); // 0000: 1 conversion in channel conversion sequence


	ADC->CCR |= BIT16;	// prescaler div 4
	ADC->CCR &= ~BIT17;
	ADC->CCR |= (BIT8 | BIT9); 		// 8 cycles Delay between 2 sampling phases
	ADC->CCR &= ~(BIT10 | BIT11);
	ADC->CCR &= ~(BIT0 | BIT1 | BIT2 | BIT3); // all ADC (1 2 and 3) are independent
	ADC->CCR &= ~(BIT14 | BIT15); // DMA disable

	ADC1->CR2 |= ADC_CR2_ADON; // enable conversion
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

void configureChannel0ADC(){
	ADC1->SMPR2 |= BIT0;			// sets channel 0 sampling time == 15 cycles
	ADC1->SMPR2 &= ~(BIT1 | BIT2);

	ADC1->SQR3 &= ~(BIT0 | BIT1 | BIT2 | BIT3 | BIT4); // set sequence of sampling for channel0 (is the first to be sample)
}

void configureChannel1ADC(){
	ADC1->SMPR2 |= BIT3;			// sets channel 1 sampling time == 15 cycles
	ADC1->SMPR2 &= ~(BIT4 | BIT5);

	ADC1->SQR3 &= ~(BIT5 | BIT6 | BIT7 | BIT8 | BIT9); // set sequence of sampling for channel1 (is the first to be sample)
}

uint16_t readADC(uint8_t channel){
	uint32_t timeout = 0xFFF;

	if (channel == 0)
		configureChannel0ADC();
	else if (channel == 1)
		configureChannel1ADC();

	ADC1->CR2 |= (uint32_t)ADC_CR2_SWSTART; // start conversion

	// wait end of conversion
	while (!(ADC1->SR & ADC_SR_EOC)) {
		// timeout if conversion too long
		if (timeout-- == 0x00) {
			return 0;
		}
	}

	return ADC1->DR;
}
