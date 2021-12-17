/*
 * encoder.c
 *
 *  Created on: 14 déc. 2021
 *      Author: eti52
 */
#include "encoder.h"

void configureTIM4(){

  RCC->APB2ENR |= BIT2; // donne horloge au peripherique TIM4

  TIM4->CR1 &= ~BIT0; // counter disable

  TIM4->CCMR1 |= BIT0;
  TIM4->CCMR1 &= ~BIT1; //channel is configured as input, IC1 is mapped on TI1
  TIM4->CCMR1 |= BIT8;
  TIM4->CCMR1 &= ~BIT9; //TIMx_CCMR2 register, TI2FP2 mapped on TI2)

  TIM4->CCER &= ~BIT1;  // CC1P=0
  TIM4->CCER &= ~BIT3;  //CC1NP=0
  TIM4->CCMR1 &= ~(BIT4 | BIT5 | BIT6 | BIT7); //IC1F = ‘0000’
  TIM4->CCER &= ~BIT5;  // CC2P=0
  TIM4->CCER &= ~BIT7;  // CC2NP=0
  TIM4->CCMR1 &= ~(BIT12 | BIT13 | BIT14 | BIT15); //IC2F = ‘0000’

  TIM4->SMCR &= ~BIT2;
  TIM4->SMCR |= (BIT0 | BIT1); // both inputs are active on both rising and falling edges

  NVIC->ISER[0] |= BIT30; // activate TIM2 in NVIC pour quil puisse traiter les interupt

  TIM4->CR1 |= BIT0; // counter enable
}
